cmake_minimum_required(VERSION 3.22)

add_library(geometry
	angles.cpp
	intersection.cpp
	linear_equation.cpp
	ray.cpp
	segment.cpp
)
	
	target_include_directories(geometry PRIVATE ${CMAKE_SOURCE_DIR}/src/libraries)