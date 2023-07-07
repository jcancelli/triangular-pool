cmake_minimum_required(VERSION 3.22)

include_directories(
	libraries
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/libraries
)

add_executable(linear_equation.test math/linear_equation.test.cpp)
add_executable(segment.test math/segment.test.cpp)
add_executable(statistics.test math/statistics.test.cpp)

target_link_libraries(linear_equation.test PRIVATE math)
target_link_libraries(segment.test PRIVATE math)
target_link_libraries(statistics.test PRIVATE math)

add_test(NAME linear_equation COMMAND linear_equation.test)
add_test(NAME segment COMMAND segment.test)
add_test(NAME statistics COMMAND statistics.test)
