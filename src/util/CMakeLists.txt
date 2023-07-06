cmake_minimum_required(VERSION 3.22)

add_library(util
	arguments.cpp
	config.cpp
)

target_include_directories(util PRIVATE ${CMAKE_SOURCE_DIR}/src/libraries)

target_link_libraries(util PRIVATE Argumentum::headers)