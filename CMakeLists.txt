cmake_minimum_required(VERSION 3.7)
project(wine_vs_goband)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AI.CPP
        AI.H
        Board.cpp
        Board.h
        decision.cpp
        decision.h
        JUDGE.cpp
        JUDGE.H
        main.cpp
        TABLE.CPP
        TABLE.H
        tools.cpp
        tools.h
        WineAI.cpp
        WineAI.h)

add_executable(wine_vs_goband ${SOURCE_FILES})