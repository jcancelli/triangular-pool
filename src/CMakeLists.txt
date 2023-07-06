cmake_minimum_required(VERSION 3.22)

add_subdirectory(geometry)
add_subdirectory(graphics)
add_subdirectory(libraries/argumentum)
add_subdirectory(util)

add_executable(triangular_pool
	main.cpp
	particle.cpp
	simulation.cpp
	wall.cpp
)

target_include_directories(triangular_pool PRIVATE ${CMAKE_SOURCE_DIR}/src/libraries)

target_link_libraries(triangular_pool PRIVATE geometry)
target_link_libraries(triangular_pool PRIVATE graphics)
target_link_libraries(triangular_pool PRIVATE util)
