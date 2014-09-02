cmake_minimum_required(VERSION 2.8)

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
    res/MainResource.qrc
)
qt5_wrap_ui(UI_SOURCES 
    ui/AboutWindow.ui
    ui/MainWindow.ui
    ui/SettingsWindow.ui
)
set(SOURCES
#    src/C_AboutWindow.cpp
#    src/C_CalibrationWindow.cpp
#    src/C_CoordinateTransform.cpp
#    src/C_DisplayMouse.cpp
#    src/C_MainWindow.cpp
#    src/C_RawMouse.cpp
#    src/C_SettingsWindow.cpp
#    src/matrix.cpp
    src/SmartPen.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# set(LIBS
# )
# target_link_libraries(${PROJECT_NAME} ${LIBS})
qt5_use_modules(${PROJECT_NAME} Widgets Core OpenGL)

# install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})