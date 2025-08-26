cmake_minimum_required(VERSION 3.31)
project(oscillator_generator)

set(CMAKE_CXX_STANDARD 23)

add_executable(oscillator_generator main.cpp)

find_package(portaudio REQUIRED)

target_link_libraries(oscillator_generator portaudio_static)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -check=*;
        -warnings-as-errors=*;)
