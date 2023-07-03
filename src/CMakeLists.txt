cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(triangular_pool
	intersection.cpp
	linear_equation.cpp
	main.cpp
	particle.cpp
	ray.cpp
	segment.cpp
	wall.cpp
)

target_include_directories(triangular_pool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries)
target_link_libraries(triangular_pool PRIVATE sfml-graphics)
