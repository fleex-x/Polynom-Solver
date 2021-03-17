cmake_minimum_required(VERSION 3.16)

project(polynom-solver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Werror -O2)
add_compile_options(-fsanitize=address -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=undefined)

add_executable(solver src/solver.cpp src/polynom.cpp)
target_include_directories(solver PUBLIC include)