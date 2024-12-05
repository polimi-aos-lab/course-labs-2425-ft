cmake_minimum_required(VERSION 3.5)
project(aos)
set(CMAKE_BULD_TYPE Release)

add_executable(program main.cpp ../common/active_object.cpp ../common/reactor.cpp)
