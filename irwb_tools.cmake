# tools macros

macro(print_repo_root  place)
	message(STATUS "${place}: ")
	message(STATUS "IR-White-Board repository root directory = ${IRWB_REPO_ROOT}")
endmacro()

macro(print_current_dir)
	message(STATUS "cur dir: ${CMAKE_CURRENT_LIST_DIR}")
endmacro()
