cmake_minimum_required(VERSION 2.8)

# find OpenCV
find_package(OpenCV 
    COMPONENTS 
        core 
        imgproc 
        highgui
)

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

    src
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(
    -std=c++11
    ${Qt5Widgets_DEFINITIONS}
    ${Qt5Core_DEFINITIONS}
    ${Qt5OpenGL_DEFINITIONS}
)

set(PROJECT_NAME irboard)
project(${PROJECT_NAME})

qt5_add_resources(RES_SOURCES
    resources/MainResource.qrc
)
qt5_wrap_ui(UI_SOURCES 
    ui/MainWindow.ui
    ui/SettingsWindow.ui
)
set(SOURCES
    src/IrCameraProcessor.cpp
    src/CalibrationWindow.cpp
    src/MainWindow.cpp
    src/SettingsWindow.cpp
    src/SmartPen.cpp
    src/Transformer.cpp
    src/CoordinateConverter.cpp
    src/Platform.cpp
    src/IrMouse.cpp
)

if(MINGW)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${RES_SOURCES} ${UI_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${RES_SOURCES} ${UI_SOURCES})
endif()

set(LIBS
    ${OpenCV_LIBRARIES} 
)
target_link_libraries(${PROJECT_NAME} ${LIBS})
qt5_use_modules(${PROJECT_NAME} Widgets Core OpenGL)

# install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
