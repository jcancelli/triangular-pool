cmake_minimum_required(VERSION 3.22)

add_library(math
	angles.cpp
	intersection.cpp
	linear_equation.cpp
	ray.cpp
	segment.cpp
)
	
	target_include_directories(math PRIVATE ${CMAKE_SOURCE_DIR}/src/libraries)