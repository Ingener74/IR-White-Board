cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ir-tester)
project(${PROJECT_NAME})

set(SOURCES
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
