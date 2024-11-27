cmake_minimum_required(VERSION 3.29)
project(LaGrande C)

set(CMAKE_C_STANDARD 11)

add_executable(LaGrande main.c
        header.h
        general.c
        modification.c
        nota.c
        helper.c
        filehandler.c
        login.h)
