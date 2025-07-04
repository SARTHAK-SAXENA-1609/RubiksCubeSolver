//
// Created by Sarthak Saxena on 23-06-2025.
//

#include "GenericRubiksCubeModel.h"

class RubiksCube3DArray : public GenericRubiksCubeModel {
    private:

    void rotateFace(int ind) {
        char temp_arr[3][3] = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_arr[i][j] = cube[ind][i][j];
            }
        }
        for (int i = 0; i < 3; i++) cube[ind][0][i] = temp_arr[2 - i][0];
        for (int i = 0; i < 3; i++) cube[ind][i][2] = temp_arr[0][i];
        for (int i = 0; i < 3; i++) cube[ind][2][2 - i] = temp_arr[i][2];
        for (int i = 0; i < 3; i++) cube[ind][2 - i][0] = temp_arr[2][2 - i];
    }

    public:
        char cube[6][3][3];
        RubiksCube3DArray() {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        cube[i][j][k] = getColorLetter(COLOR(i));
                    }
                }
            }
        }

        COLOR getColor(FACE face, unsigned row, unsigned col) const override {
            char color = cube[int(face)][row][col];
            if (color == 'B') {
                return COLOR::BLUE;
            }
            else if (color == 'G') {
                return COLOR::GREEN;
            }
            else if (color == 'R') {
                return COLOR::RED;
            }
            else if (color == 'Y') {
                return COLOR::YELLOW;
            }
            else if (color == 'W') {
                return COLOR::WHITE;
            }
            return COLOR::ORANGE;
        }

        bool isSolved() const override {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (this->cube[i][j][k] == getColorLetter(COLOR(i))) continue;
                        return false;
                    }
                }
            }
            return true;
        }

    GenericRubiksCubeModel &u() override {
        this->rotateFace(0);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[4][0][2 - i];
        for (int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
        for (int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
        for (int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
        for (int i = 0; i < 3; i++) cube[3][0][2 - i] = temp_arr[i];

        return *this;
    }

    GenericRubiksCubeModel &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    }

    GenericRubiksCubeModel &u2() override {
        this->u();
        this->u();

        return *this;
    }

    GenericRubiksCubeModel &l() override {
        this->rotateFace(1);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][i][0];
        for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
        for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
        for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for (int i = 0; i < 3; i++) cube[2][i][0] = temp_arr[i];

        return *this;
    }

    GenericRubiksCubeModel &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    }

    GenericRubiksCubeModel &l2() override {
        this->l();
        this->l();

        return *this;
    }

    GenericRubiksCubeModel &f() override {
        this->rotateFace(2);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = temp_arr[i];

        return *this;
    }

    GenericRubiksCubeModel &fPrime() override {
        this->f();
        this->f();
        this->f();

        return *this;
    }

    GenericRubiksCubeModel &f2() override {
        this->f();
        this->f();

        return *this;
    }

    GenericRubiksCubeModel &r() override {
        this->rotateFace(3);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = temp_arr[i];

        return *this;
    }

    GenericRubiksCubeModel &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    }

    GenericRubiksCubeModel &r2() override {
        this->r();
        this->r();

        return *this;
    }

    GenericRubiksCubeModel &b() override {
        this->rotateFace(4);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = temp_arr[i];

        return *this;
    }

    GenericRubiksCubeModel &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    }

    GenericRubiksCubeModel &b2() override {
        this->b();
        this->b();

        return *this;
    }

    GenericRubiksCubeModel &d() override {
        this->rotateFace(5);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = temp_arr[i];

        return *this;
    }

    GenericRubiksCubeModel &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    }

    GenericRubiksCubeModel &d2() override {
        this->d();
        this->d();

        return *this;
    }

    bool operator==(const RubiksCube3DArray &r1) const {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (r1.cube[i][j][k] != cube[i][j][k]) return false;
                    }
                }
            }
            return true;
        }

    RubiksCube3DArray &operator = (const RubiksCube3DArray &r1) {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        cube[i][j][k] = r1.cube[i][j][k];
                    }
                }
            }
            return *this;
        }
};

struct Hash3d {
    size_t operator()(const RubiksCube3DArray &r1) const {
        string str = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += r1.cube[i][j][k];
                }
            }
        }
        return hash<string>()(str);
    }

};