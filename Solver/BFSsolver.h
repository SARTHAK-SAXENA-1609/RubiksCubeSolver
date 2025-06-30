//
// Created by sarsa on 29-06-2025.
//

#include<bits/stdc++.h>
#include"../Models/GenericRubiksCubeModel.h"

#ifndef BFSSOLVER_H
#define BFSSOLVER_H

template<typename T , typename H>
class BFSsolver {
    private:
        vector<GenericRubiksCubeModel::MOVE>moves;
        unordered_map<T , bool , H>visited;
        unordered_map<T , GenericRubiksCubeModel::MOVE , H>move_done;

        T bfs() {
            queue<T>q;
            // T state = RubiksCube;
            q.push(RubiksCube);
            visited[RubiksCube] = true;
            while (!q.empty()) {
                T& state = q.front();
                q.pop();
                if (state.isSolved()) {
                    return state;
                }
                for (int i=0;i<18;i++) {
                    auto cur_move = GenericRubiksCubeModel::MOVE(i);
                    state.move(cur_move);
                    if (!visited[state]) {
                        visited[state] = true;
                        move_done[state] = cur_move;
                        q.push(state);
                    }
                    state.invert(cur_move);
                }
            }
            return RubiksCube;
        }

    public:

    T RubiksCube;
    BFSsolver(T rubiksCube) {
        RubiksCube = rubiksCube;
    }
    vector<GenericRubiksCubeModel::MOVE> solve() {
        T solved_cube = bfs();
        assert(solved_cube.isSolved());

        T curr_cube = solved_cube;
        while (!(curr_cube == RubiksCube)) {
            GenericRubiksCubeModel::MOVE cur_move = move_done[curr_cube];
            moves.push_back(cur_move);
            curr_cube.invert(cur_move);
        }
        RubiksCube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};


#endif //BFSSOLVER_H
