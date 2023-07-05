cmake_minimum_required(VERSION 3.22)

include_directories(
	libraries
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/libraries
)

add_executable(linear_equation.test linear_equation.test.cpp)
add_executable(segment.test segment.test.cpp)

target_link_libraries(linear_equation.test PRIVATE geometry)
target_link_libraries(segment.test PRIVATE geometry)

add_test(NAME linear_equation COMMAND linear_equation.test)
add_test(NAME segment COMMAND segment.test)
