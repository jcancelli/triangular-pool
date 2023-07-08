cmake_minimum_required(VERSION 3.22)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/libraries)

add_library(graphics
	font.cpp
	graphics.cpp
	particle.cpp
	point.cpp
	simulation.cpp
	wall.cpp
	window.cpp
)

target_link_libraries(graphics PUBLIC sfml-graphics)