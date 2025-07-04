//
// Created by sarsa on 01-07-2025.
//

#include<bits/stdc++.h>
#include"../Models/GenericRubiksCubeModel.h"
#include"DFSSolver.h"

#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H

template<typename T , typename H>
class IDDFSsolver {
private:
    int max_search_depth;
    vector<GenericRubiksCubeModel::MOVE> moves;
public:
    T RubiksCube;
    IDDFSsolver(T _RubiksCube, int msd) {
        max_search_depth = msd;
        RubiksCube = _RubiksCube;
    }

    vector<GenericRubiksCubeModel::MOVE> solve() {
        for (int i=1;i<=max_search_depth;i++) {
            DFSsolver<T,H> dfssolver(RubiksCube,i);
            moves = dfssolver.solve();
            if (dfssolver.RubiksCube.isSolved()) {
                RubiksCube = dfssolver.RubiksCube;
                break;
            }
        }
        return moves;


    }
};





#endif //IDDFSSOLVER_H
