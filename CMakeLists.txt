#
# DBOF
# Copyright 2017 glyre
#

cmake_minimum_required(VERSION 3.5)
project(dbof)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(DBOF_INCLUDE_FILES
        include/dbof/dbof.h
        include/dbof/dbof.hpp
        include/dbof/file.h
        include/dbof/stream.hpp)

set(DBOF_SRC_FILES
        src/dbof.c)

add_library(dbof ${DBOF_INCLUDE_FILES} ${DBOF_SRC_FILES})
target_include_directories(dbof PRIVATE include/)
