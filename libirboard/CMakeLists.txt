cmake_minimum_required(VERSION 3.0)

if(MINGW)
    add_definitions(-std=c++11)
else()
    add_definitions(-std=c++11 -fPIC)
endif()

# IrBoard library

set(LIBRARY_NAME IrBoard)
set(LIBRARY_SOURCES
    IrBoard.cpp 
    IrBoard.h
)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

# IrBoard SWIG python wrapper

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(PythonLibs 2.7 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PYTHON_INCLUDE_PATH}
)

set(MODULE_NAME ${LIBRARY_NAME})
set(MODULE_FILE "${MODULE_NAME}.i")

set(CMAKE_SWIG_FLAGS "-c++")
set_source_files_properties(${MODULE_FILE} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${MODULE_FILE} PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

set(LIBS
    IrBoard
)

SWIG_ADD_MODULE(${LIBRARY_NAME} python ${MODULE_FILE})
SWIG_LINK_LIBRARIES(${LIBRARY_NAME} ${LIBS} ${PYTHON_LIBRARIES})
