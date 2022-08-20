cmake_minimum_required(VERSION 3.10)
project(net-dir VERSION 1.0.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")
add_executable(netfiler.server server/server.c)
