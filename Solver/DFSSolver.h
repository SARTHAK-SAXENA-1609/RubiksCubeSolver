//
// Created by sarsa on 29-06-2025.
//

#include<bits/stdc++.h>
#include"../Models/GenericRubiksCubeModel.h"

#ifndef DFSSOLVER_H
#define DFSSOLVER_H

template<typename T , typename H >
class DFSsolver {
    private:
    vector<GenericRubiksCubeModel::MOVE> moves;
    int max_search_depth;

    bool dfs(int depth) {
        if (RubiksCube.is_solved())return true;
        if (depth > max_search_depth)return false;
        for (int i=0;i<18;i++) {
            RubiksCube.move(GenericRubiksCubeModel::MOVE(i));
            moves.push_back(GenericRubiksCubeModel::MOVE(i));
            dfs(depth+1);
            moves.pop_back();
            RubiksCube.invert(GenericRubiksCubeModel::MOVE(i));
        }
        return false;
    }

    public:
    T RubiksCube;
    DFSsolver(T _RubiksCube, int msd) {
        RubiksCube = _RubiksCube;
        max_search_depth = msd;
    }
    vector<GenericRubiksCubeModel::MOVE> solve() {
        dfs(1);
        return moves;
    }
};

#endif //DFSSOLVER_H
