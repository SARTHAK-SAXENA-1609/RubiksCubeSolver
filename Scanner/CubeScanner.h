//
// Created by sarsa on 30-08-2025.
//

#ifndef CUBESCANNER_H
#define CUBESCANNER_H

#include <opencv2/opencv.hpp>
#include "GenericRubiksCubeModel.h"
#include "bits/stdc++.h"

using namespace std;
using namespace cv;

class CubeScanner {
public:
    CubeScanner(int camIndex = 0, int boxSize = 60);
    ~CubeScanner();

    void scan(GenericRubiksCubeModel& cube);

private:
    VideoCapture cap;
    int boxSize;

    static const map<GenericRubiksCubeModel::COLOR, Scalar> colorMap;

    GenericRubiksCubeModel::COLOR classifyColor(const Vec3b& bgr);
    Vec3b medianColor(const Mat& frame, int centerX, int centerY, int region = 5);

    vector<vector<GenericRubiksCubeModel::COLOR>> captureFace();
    Mat drawColorFace(const vector<vector<GenericRubiksCubeModel::COLOR>>& faceGrid);
    Mat drawFullCube(const vector<vector<vector<GenericRubiksCubeModel::COLOR>>>& cubeGrid);
};



#endif //CUBESCANNER_H
