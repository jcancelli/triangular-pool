cmake_minimum_required(VERSION 3.22)

include_directories(
	libraries
	${CMAKE_SOURCE_DIR}/src
)

add_executable( linear_equation.test
	linear_equation.test.cpp
	${CMAKE_SOURCE_DIR}/src/linear_equation.cpp
)
add_test(NAME linear_equation COMMAND linear_equation.test)
