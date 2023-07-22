cmake_minimum_required(VERSION 3.25)
project(picture_socket)

set(CMAKE_CXX_STANDARD 14)

add_executable(picture_socket
        server.cpp)
