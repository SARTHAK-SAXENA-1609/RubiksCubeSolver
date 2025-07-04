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
        Solver/IDDFSsolver.h
        PatternDatabases/math.cpp
        PatternDatabases/math.h
        PatternDatabases/PermutationIndexer.h
        PatternDatabases/NibbleArray.cpp
        PatternDatabases/NibbleArray.h
        PatternDatabases/PatternDatabase.cpp
        PatternDatabases/PatternDatabase.h
        PatternDatabases/CornerPatternDatabase.cpp
        PatternDatabases/CornerPatternDatabase.h
        PatternDatabases/CornerDBMaker.cpp
        PatternDatabases/CornerDBMaker.h
        Solver/IDAstarSolver.h
)
