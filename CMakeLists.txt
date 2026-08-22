cmake_minimum_required(VERSION 4.3)

project(rule30 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_source_files_properties(rule30_avx2.cpp PROPERTIES COMPILE_OPTIONS -march=x86-64-v3)
set_source_files_properties(rule30_avx512.cpp PROPERTIES COMPILE_OPTIONS -march=x86-64-v4)
add_executable(rule30 main.cpp rule30.cpp rule30_avx2.cpp rule30_avx512.cpp certifier.cpp)
target_compile_options(rule30 PRIVATE -Wall -Wextra)
