cmake_minimum_required(VERSION 3.20)
project(fifteenki)

set(CMAKE_CXX_STANDARD 23)

add_executable(fifteenki main.cpp Game.cpp Game.h WalkingDistance.cpp WalkingDistance.h Util.h Util.cpp)
