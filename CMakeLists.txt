cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

include(PCHSupport)

if(MINGW)
    message("Configured for MinGW")
    add_definitions(-DMINGW)
elseif(APPLE)
    message("Configured for MacOS X")
    add_definitions(-DMACOSX)
else()
    message("Configured for Linux GCC")
    add_definitions(-DLINUX)
endif()

# find boost
find_package(Boost 1.53.0 REQUIRED system program_options)

# find OpenCV
find_package(OpenCV 
    COMPONENTS 
        core 
        imgproc 
        highgui
)

# find OpenGL
find_package(OpenGL)

# find Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core    REQUIRED)
find_package(Qt5OpenGL  REQUIRED)

include_directories(
    ${Qt5Widgets_INCLUDES}
    ${Qt5Core_INCLUDES}
    ${Qt5OpenGL_INCLUDES}

    ${OpenCV_INCLUDE_DIRS}

    ${Boost_INCLUDE_DIRS}
)

add_definitions(
    -std=c++11
)

file(COPY data/monitor.png DESTINATION ${CMAKE_BINARY_DIR})

# apps
add_subdirectory(ir-tester)

add_subdirectory(irboard)
