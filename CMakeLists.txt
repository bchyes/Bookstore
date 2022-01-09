cmake_minimum_required(VERSION 3.16)
project(Bookstore)

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR}/src)
set(src_dir
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        src/OperationFunction.cpp
        src/Log.cpp
        src/BookNode.cpp
        src/PeopleNode.cpp
        src/People.cpp)

add_executable(code ${src_dir} src/main.cpp)
