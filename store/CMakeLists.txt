cmake_minimum_required(VERSION 3.16)
project(store)

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR}/src)
set(src_dir ${PROJECT_SOURCE_DIR}/src/template.h)
add_executable(store ${src_dir} src/main_template.cpp)
