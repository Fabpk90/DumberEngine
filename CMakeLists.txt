cmake_minimum_required(VERSION 3.15)
project("DumberEngine")

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

link_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/external)

add_subdirectory(DumberEngine/sources)