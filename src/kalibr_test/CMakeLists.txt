cmake_minimum_required(VERSION 2.8)
project(kalibr_test)
add_compile_options(-std=c++11)

include_directories(/usr/include/eigen3)
add_executable(2d_to_3d keyPointToEuclidean.cpp)