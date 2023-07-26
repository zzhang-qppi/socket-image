cmake_minimum_required(VERSION 3.25)
project(socket_image)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(socket_image
        client.c
        server.c)
