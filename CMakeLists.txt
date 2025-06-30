cmake_minimum_required(VERSION 3.31)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(RubiksCubeSolver main.cpp
        Models/GenericRubiksCubeModel.cpp
        Models/GenericRubiksCubeModel.h
        Models/RubiksCube3DArray.cpp
        Models/RubiksCube1DArray.cpp
        Models/RubiksCubeBitboard.cpp
        Solver/DFSSolver.h
        Solver/BFSsolver.h
)
