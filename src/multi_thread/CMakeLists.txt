cmake_minimum_required(VERSION 2.8.3)
project(thread_learn)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
find_package(Threads)

add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test ${CMAKE_THREAD_LIBS_INIT})
