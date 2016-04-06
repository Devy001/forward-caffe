project(jaffe)

#set(SOURCE_FILES blob.cpp jmatch.cpp layer.cpp net.cpp rawdata.cpp io.cpp math_function.cpp)
aux_source_directory(. SOURCE_FILES)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_library(jaffe SHARED ${SOURCE_FILES})

ADD_LIBRARY(jaffe_static STATIC ${SOURCE_FILES})
SET_TARGET_PROPERTIES(jaffe_static PROPERTIES OUTPUT_NAME "jaffe")
#SET_TARGET_PROPERTIES(jaffe_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/lib")
SET_TARGET_PROPERTIES(jaffe PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(jaffe_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)