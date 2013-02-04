cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME irboard)
project(${PROJECT_NAME})

set(SOURCES 
    src/main.cpp
    )
    
add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})