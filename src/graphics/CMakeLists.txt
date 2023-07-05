cmake_minimum_required(VERSION 3.22)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_library(graphics
	simulation.cpp
)

target_link_libraries(graphics PUBLIC sfml-graphics)