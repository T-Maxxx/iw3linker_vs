cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
project(iw3linker_vs)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INC src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SRC} ${INC})
target_include_directories(${PROJECT_NAME} PRIVATE src)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC} ${INC})
