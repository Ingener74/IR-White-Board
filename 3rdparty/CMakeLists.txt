cmake_minimum_required(VERSION 2.8)

add_custom_target(
	untar3rdparty
	tar -xvf ${CMAKE_CURRENT_LIST_DIR}/OpenCV-2.4.4a.tar.bz2 -C ${CMAKE_CURRENT_LIST_DIR}
)
