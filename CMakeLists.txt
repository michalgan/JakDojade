cmake_minimum_required(VERSION 3.25)
project(JakDojade)

set(CMAKE_CXX_STANDARD 17)

add_executable(JakDojade main.cpp Connection.h String.cpp Query.h Navigator.cpp Navigator.h Coordinates.h City.h Edge.h Graph.h Vertex.h)
