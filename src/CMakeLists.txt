cmake_minimum_required(VERSION 3.27)
project(DA_Proj2)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_Proj2 main.cpp
        data_structures/GraphConstructor.cpp
        Manager.cpp
        Manager.h
        Menu.cpp
        Menu.h)
