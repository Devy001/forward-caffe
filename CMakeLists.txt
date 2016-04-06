cmake_minimum_required(VERSION 3.5)
project(jaffe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

#set(SOURCE_FILES main.cpp)
#add_executable(jaffe ${SOURCE_FILES})

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/layer
        ${PROJECT_SOURCE_DIR}/include/parameter
        ${PROJECT_SOURCE_DIR}/include/util

        /usr/local/include
        /usr/include
)

link_directories(
        ${PROJECT_BINARY_DIR}/lib

        /usr/local/lib
        /use/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)



