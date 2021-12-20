cmake_minimum_required(VERSION 3.11)

project(final LANGUAGES CXX)

add_executable(calc
        main.cpp
        models.h
        models.cpp logs.cpp logs.h parser.cpp parser.h calculator.cpp calculator.h)
