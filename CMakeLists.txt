cmake_minimum_required(VERSION 3.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(dpaligner CXX)

include_directories(${PROJECT_SOURCE_DIR}/external/catch/single_include)

add_subdirectory(source)
add_subdirectory(test)
