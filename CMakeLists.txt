cmake_minimum_required(VERSION 2.8)

include(irwb_tools.cmake)

set(IRWB_REPO_ROOT ${CMAKE_CURRENT_LIST_DIR})

print_repo_root("main cmake")
print_current_dir()

add_subdirectory(3rdparty)
add_subdirectory(apps)
