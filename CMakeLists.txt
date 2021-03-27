cmake_minimum_required(VERSION 3.17)
project(cpptmp_scheme)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(test_rec src/test_rec.cpp)
add_executable(test_sexp src/test_sexp.cpp)
add_executable(test_basic src/test_basic.cpp)
add_executable(numerics src/numerics.cpp)
add_executable(lists src/lists.cpp)
add_executable(scheme src/scheme.cpp)