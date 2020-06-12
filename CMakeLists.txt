cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
project(iw3linker_vs)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INC src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SRC} ${INC})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC} ${INC})

set(LINKER_PATCH_DEPLOY_DIR $ENV{LINKER_PATCH_DEPLOY_DIR})
if (LINKER_PATCH_DEPLOY_DIR)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E echo "Copying library to game directory: ${LINKER_PATCH_DEPLOY_DIR}"
        COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${PROJECT_NAME}>" "${LINKER_PATCH_DEPLOY_DIR}/lnkpatch.dll"
    )
endif()