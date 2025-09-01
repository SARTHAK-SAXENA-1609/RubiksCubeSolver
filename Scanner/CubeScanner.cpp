//
// Created by sarsa on 30-08-2025.
//

#include "CubeScanner.h"


#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace cv;
using namespace std;

// Static color map definition
const map<GenericRubiksCubeModel::COLOR, Scalar> CubeScanner::colorMap = {
    {GenericRubiksCubeModel::COLOR::WHITE,  Scalar(255, 255, 255)},
    {GenericRubiksCubeModel::COLOR::RED,    Scalar(0, 0, 255)},
    {GenericRubiksCubeModel::COLOR::ORANGE, Scalar(0, 165, 255)},
    {GenericRubiksCubeModel::COLOR::YELLOW, Scalar(0, 255, 255)},
    {GenericRubiksCubeModel::COLOR::GREEN,  Scalar(0, 255, 0)},
    {GenericRubiksCubeModel::COLOR::BLUE,   Scalar(255, 0, 0)},
    {GenericRubiksCubeModel::COLOR::UNKNOWN, Scalar(50, 50, 50)}
};

CubeScanner::CubeScanner(int camIndex, int boxSize) : boxSize(boxSize) {
    cap.open(camIndex);
    if (!cap.isOpened()) {
        throw runtime_error("Failed to open webcam");
    }
}

CubeScanner::~CubeScanner() {
    if (cap.isOpened()) {
        cap.release();
    }
    destroyAllWindows();
}

/**
 * @brief Classifies a color based on its BGR value.
 *
 * This optimized function converts the BGR color to the HSV color space,
 * which is more reliable for color detection under varying lighting conditions.
 * It uses thresholds for Hue, Saturation, and Value to accurately identify
 * the six Rubik's Cube colors.
 *
 * - White is detected by its very low saturation and high brightness.
 * - Other colors are detected based on their specific Hue range, while also
 * ensuring they have sufficient saturation and brightness to avoid
 * misclassifying shadows or grey areas.
 * - Red is handled as a special case because its hue range wraps around 0 in OpenCV's scale.
 *
 * @param bgr The color to classify in BGR format.
 * @return The corresponding GenericRubiksCubeModel::COLOR enum value.
 */
GenericRubiksCubeModel::COLOR CubeScanner::classifyColor(const Vec3b& bgr) {
    Mat bgrPixel(1, 1, CV_8UC3, Scalar(bgr[0], bgr[1], bgr[2]));
    Mat hsvPixel;
    cvtColor(bgrPixel, hsvPixel, COLOR_BGR2HSV);

    Vec3b hsv = hsvPixel.at<Vec3b>(0, 0);
    int h = hsv[0]; // Hue (0-179)
    int s = hsv[1]; // Saturation (0-255)
    int v = hsv[2]; // Value/Brightness (0-255)

    // Note: These HSV thresholds may need slight tuning for your specific
    // camera, lighting conditions, and cube shades.

    // White: Low saturation, high value
    if (s < 50 && v > 150) {
        return GenericRubiksCubeModel::COLOR::WHITE;
    }

    // Filter out grey/black/shadows based on low saturation or value
    if (s < 80 || v < 70) {
        return GenericRubiksCubeModel::COLOR::UNKNOWN;
    }

    // Red: Hue is at the beginning/end of the spectrum
    if (h < 8 || h > 165) {
        return GenericRubiksCubeModel::COLOR::RED;
    }
    // Orange
    if (h >= 8 && h < 20) {
        return GenericRubiksCubeModel::COLOR::ORANGE;
    }
    // Yellow
    if (h >= 20 && h < 35) {
        return GenericRubiksCubeModel::COLOR::YELLOW;
    }
    // Green
    if (h >= 40 && h < 85) {
        return GenericRubiksCubeModel::COLOR::GREEN;
    }
    // Blue
    if (h >= 90 && h < 130) {
        return GenericRubiksCubeModel::COLOR::BLUE;
    }

    return GenericRubiksCubeModel::COLOR::UNKNOWN;
}


/**
 * @brief Calculates the median color of a small square region in the frame.
 *
 * Using the median color instead of the average helps to reduce noise from
 * camera sensors and ignore outliers caused by glare or reflections.
 *
 * @param frame The input camera frame.
 * @param centerX The center x-coordinate of the region.
 * @param centerY The center y-coordinate of the region.
 * @param regionSize The size of the square region to sample.
 * @return The median color of the region in BGR format.
 */
Vec3b CubeScanner::medianColor(const Mat& frame, int centerX, int centerY, int regionSize) {
    int half = regionSize / 2;
    vector<uchar> B, G, R;

    for (int dy = -half; dy <= half; ++dy) {
        for (int dx = -half; dx <= half; ++dx) {
            int x = centerX + dx;
            int y = centerY + dy;
            if (x >= 0 && x < frame.cols && y >= 0 && y < frame.rows) {
                Vec3b bgr = frame.at<Vec3b>(y, x);
                B.push_back(bgr[0]);
                G.push_back(bgr[1]);
                R.push_back(bgr[2]);
            }
        }
    }

    if (B.empty()) return Vec3b(0,0,0);

    sort(B.begin(), B.end());
    sort(G.begin(), G.end());
    sort(R.begin(), R.end());

    int mid = B.size() / 2;
    return Vec3b(B[mid], G[mid], R[mid]);
}

vector<vector<GenericRubiksCubeModel::COLOR>> CubeScanner::captureFace() {
    Mat frame;
    int rows = 0, cols = 0;

    while (true) {
        if (!cap.read(frame)) {
            cerr << "ERROR: Could not read frame from camera." << endl;
            break;
        }

        rows = frame.rows;
        cols = frame.cols;
        int startX = (cols - 3 * boxSize) / 2;
        int startY = (rows - 3 * boxSize) / 2;

        // Draw the 3x3 grid overlay
        for (int i = 0; i <= 3; ++i) {
            line(frame, Point(startX, startY + i * boxSize), Point(startX + 3 * boxSize, startY + i * boxSize), Scalar(255, 255, 255), 2);
            line(frame, Point(startX + i * boxSize, startY), Point(startX + i * boxSize, startY + 3 * boxSize), Scalar(255, 255, 255), 2);
        }

        putText(frame, "Press SPACE to capture, ESC to exit", Point(30, 30),
                FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2, LINE_AA);

        imshow("Align Cube Face", frame);

        int key = waitKey(30);
        if (key == 32) break;  // SPACE -> capture
        if (key == 27) {       // ESC -> quit
            cap.release();
            destroyAllWindows();
            exit(0);
        }
    }

    // Capture the final frame for processing
    cap.read(frame);
    int startX = (cols - 3 * boxSize) / 2;
    int startY = (rows - 3 * boxSize) / 2;

    vector<vector<GenericRubiksCubeModel::COLOR>> face(3, vector<GenericRubiksCubeModel::COLOR>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int x = startX + j * boxSize + boxSize / 2;
            int y = startY + i * boxSize + boxSize / 2;
            Vec3b bgr = medianColor(frame, x, y, 10); // Sample a 10x10 region
            face[i][j] = classifyColor(bgr);
        }
    }
    return face;
}

Mat CubeScanner::drawColorFace(const vector<vector<GenericRubiksCubeModel::COLOR>>& faceGrid) {
    int gridSize = 3 * boxSize;
    int padding = 50;
    Mat result(gridSize + padding, gridSize, CV_8UC3, Scalar(20, 20, 20));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Rect box(j * boxSize, i * boxSize, boxSize, boxSize);
            rectangle(result, box, colorMap.at(faceGrid[i][j]), FILLED);
            rectangle(result, box, Scalar(0, 0, 0), 2); // Black border for each sticker
        }
    }

    putText(result, "Press [R] to rescan or [N] for next", Point(10, gridSize + 35), FONT_HERSHEY_SIMPLEX, 0.45, Scalar(255, 255, 255), 1, LINE_AA);
    return result;
}

Mat CubeScanner::drawFullCube(const vector<vector<vector<GenericRubiksCubeModel::COLOR>>>& cubeGrid) {
    int gap = 5;
    int gridWidth = 3 * boxSize;
    int gridHeight = 3 * boxSize;
    int totalWidth = 4 * gridWidth;
    int totalHeight = 3 * gridHeight;

    Mat canvas(totalHeight, totalWidth, CV_8UC3, Scalar(30, 30, 30));

    auto drawFace = [&](int faceIndex, int startRow, int startCol) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int x = startCol + j * boxSize;
                int y = startRow + i * boxSize;
                Rect rect(x + gap/2, y + gap/2, boxSize - gap, boxSize - gap);
                rectangle(canvas, rect, colorMap.at(cubeGrid[faceIndex][i][j]), FILLED);
            }
        }
    };

    // Standard cube net layout (U, L, F, R, B, D)
    drawFace(0, 0, gridWidth);                          // Up (White/Yellow)
    drawFace(1, gridHeight, 0);                         // Left (Orange/Red)
    drawFace(2, gridHeight, gridWidth);                 // Front (Green/Blue)
    drawFace(3, gridHeight, 2 * gridWidth);             // Right (Red/Orange)
    drawFace(4, gridHeight, 3 * gridWidth);             // Back (Blue/Green)
    drawFace(5, 2 * gridHeight, gridWidth);             // Down (Yellow/White)

    return canvas;
}

void CubeScanner::scan(GenericRubiksCubeModel& cube) {
    vector<vector<vector<GenericRubiksCubeModel::COLOR>>> cubeGrid(6, vector<vector<GenericRubiksCubeModel::COLOR>>(3, vector<GenericRubiksCubeModel::COLOR>(3, GenericRubiksCubeModel::COLOR::UNKNOWN)));

    const vector<string> facePrompts = {
        "Show UP face (usually White)",
        "Show LEFT face (usually Orange)",
        "Show FRONT face (usually Green)",
        "Show RIGHT face (usually Red)",
        "Show BACK face (usually Blue)",
        "Show DOWN face (usually Yellow)"
    };

    for (int face = 0; face < 6; ++face) {
        while (true) {
            cout << "Please show the " << facePrompts[face] << " and press SPACE." << endl;
            auto grid = captureFace();
            cubeGrid[face] = grid;

            Mat faceImg = drawColorFace(grid);
            Mat cubeImg = drawFullCube(cubeGrid);

            imshow("Scanned Face", faceImg);
            imshow("Cube Net", cubeImg);

            int key = waitKey(0);
            if (key == 'n' || key == 'N') {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        cube.setColor(static_cast<GenericRubiksCubeModel::FACE>(face), i, j, grid[i][j]);
                    }
                }
                destroyWindow("Scanned Face");
                break;
            }
            if(key == 'r' || key == 'R'){
                cout << "Rescanning face..." << endl;
                destroyWindow("Scanned Face");
                // The loop will continue, prompting for a rescan
            }
        }
    }

    if (cap.isOpened()) {
        cap.release();
    }
    destroyAllWindows();
    cout << "Cube scanning complete!" << endl;
}
