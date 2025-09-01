
//
// Created by Sarthak Saxena.
//

#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include "bits/stdc++.h"

using namespace std;

class GenericRubiksCubeModel {
public:
    enum class FACE {
        UP,
        LEFT,
        FRONT,
        RIGHT,
        BACK,
        DOWN
    };

    enum class COLOR {
        WHITE,
        GREEN,
        RED,
        BLUE,
        ORANGE,
        YELLOW,
        UNKNOWN
    };

    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };

    /*
     * Returns the color of the cell at (row, col) in face.
     * If Rubik's Cube face is pointing at you, then the row numbering starts from the
     * top to bottom, and column numbering starts from the left to right.
     * The rows and columns are 0-indexed.
     */
    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

    /*
     * Sets the color of the cell at (row, col) in the given face.
     * If Rubik's Cube face is pointing at you, then the row numbering starts from the
     * top to bottom, and column numbering starts from the left to right.
     * The rows and columns are 0-indexed.
     * @param Face, row, column and color.
     */
    virtual void setColor(FACE face, int row, int col, COLOR color) = 0;

    /*
     * Returns the first letter of the given COLOR
     */
    static char getColorLetter(COLOR color);

    /*
     * Returns true if the Rubik Cube is solved, otherwise returns false.
     */
    virtual bool isSolved() const = 0;

    /*
     * Returns the move in the string format.
     */
    static string getMove(MOVE ind);

    /*
     * Print the Rubik Cube in Planar format.
     *
     * The cube is laid out as follows.
     *
     * The sides:
     *    U
     *  L F R B
     *    D
     *
     * Color wise:
     *
     *          W W W
     *          W W W
     *          W W W
     *
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *
     *          Y Y Y
     *          Y Y Y
     *          Y Y Y
     *
     */
    void print() const;

    /*
     * Randomly shuffle the cube with 'times' moves and returns the moves performed.
     */
    vector<MOVE> randomShuffleCube(unsigned int times);

    /*
     * Perform moves on the Rubik Cube
     */
    GenericRubiksCubeModel &move(MOVE ind);

    /*
     * Invert a move
     */
    GenericRubiksCubeModel &invert(MOVE ind);

    /*
     * Rotational Moves on the Rubik Cubes
     *
     * F, F’, F2,
     * U, U’, U2,
     * L, L’, L2,
     * D, D’, D2,
     * R, R’, R2,
     * B, B’, B2
     */

    virtual GenericRubiksCubeModel &f() = 0;

    virtual GenericRubiksCubeModel &fPrime() = 0;

    virtual GenericRubiksCubeModel &f2() = 0;

    virtual GenericRubiksCubeModel &u() = 0;

    virtual GenericRubiksCubeModel &uPrime() = 0;

    virtual GenericRubiksCubeModel &u2() = 0;

    virtual GenericRubiksCubeModel &l() = 0;

    virtual GenericRubiksCubeModel &lPrime() = 0;

    virtual GenericRubiksCubeModel &l2() = 0;

    virtual GenericRubiksCubeModel &r() = 0;

    virtual GenericRubiksCubeModel &d() = 0;

    virtual GenericRubiksCubeModel &dPrime() = 0;

    virtual GenericRubiksCubeModel &d2() = 0;

    virtual GenericRubiksCubeModel &rPrime() = 0;

    virtual GenericRubiksCubeModel &r2() = 0;

    virtual GenericRubiksCubeModel &b() = 0;

    virtual GenericRubiksCubeModel &bPrime() = 0;

    virtual GenericRubiksCubeModel &b2() = 0;

    string getCornerColorString(uint8_t ind) const;

    uint8_t getCornerIndex(uint8_t ind) const;

    uint8_t getCornerOrientation(uint8_t ind) const;
};


#endif //RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H