cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME irboard)
project(${PROJECT_NAME})

include_directories(
    src
)

qt5_add_resources(RES_SOURCES
    resources/MainResource.qrc
)

qt5_wrap_ui(UI_SOURCES 
    ui/MainWindow.ui
    ui/SettingsWindow.ui
)

set(HEADERS
    src/CalibrationWindow.h
    src/CoordConverter.h
    src/CoordinateConverter.h
    src/IrCameraProcessor.h
    src/IrMouse.h
    src/MainWindow.h
    src/Platform.h
    src/SettingsWindow.h
    src/Transformer.h
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

file(COPY ../data/config.json DESTINATION ${CMAKE_BINARY_DIR})

# add_precompiled_header(irboard src/precompiled_headers.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(
    ${Qt5Widgets_DEFINITIONS}
    ${Qt5Core_DEFINITIONS}
    ${Qt5OpenGL_DEFINITIONS}
)

if(MINGW)
    set(HEADERS ${HEADERS}
        src/WinPlatform.h
    )
    set(SOURCES ${SOURCES}
        src/WinPlatform.cpp
        # resources/res.rc
    )
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${RES_SOURCES} ${UI_SOURCES})
elseif(APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${RES_SOURCES} ${UI_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${RES_SOURCES} ${UI_SOURCES})
endif()

set(LIBS ${OpenCV_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${Boost_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${LIBS})
qt5_use_modules(${PROJECT_NAME} Widgets Core OpenGL)

# install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
