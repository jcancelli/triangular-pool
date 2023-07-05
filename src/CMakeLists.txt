cmake_minimum_required(VERSION 3.22)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_subdirectory(geometry)
add_subdirectory(libraries/argumentum)

add_executable(triangular_pool
	arguments.cpp
	config.cpp
	main.cpp
	particle.cpp
	simulation.cpp
	wall.cpp
)

target_include_directories(triangular_pool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

target_link_libraries(triangular_pool PRIVATE geometry)
target_link_libraries(triangular_pool PRIVATE sfml-graphics)
target_link_libraries(triangular_pool PRIVATE Argumentum::headers)
