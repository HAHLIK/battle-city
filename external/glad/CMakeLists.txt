cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(GLAD)

add_library(GLAD STATIC include/glad/glad.h src/glad.c)
target_include_directories(GLAD PUBLIC include/)