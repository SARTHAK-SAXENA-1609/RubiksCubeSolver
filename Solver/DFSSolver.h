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
        if (RubiksCube.isSolved()){ return true;}
        if (depth > max_search_depth)return false;
        for (int i=0;i<18;i++) {
            RubiksCube.move(GenericRubiksCubeModel::MOVE(i));
            moves.push_back(GenericRubiksCubeModel::MOVE(i));
            if (dfs(depth+1)) return true;
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
        bool flag = dfs(1);
        return moves;
    }
};

#endif //DFSSOLVER_H
