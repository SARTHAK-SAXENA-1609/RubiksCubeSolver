cmake_minimum_required(VERSION 3.31)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(Models)
include_directories(${CMAKE_SOURCE_DIR})

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
        Scanner/CubeScanner.cpp
        Scanner/CubeScanner.h
)

target_link_libraries(RubiksCubeSolver PRIVATE opencv_core opencv_imgproc opencv_highgui)