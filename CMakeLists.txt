cmake_minimum_required(VERSION 3.19...3.22)
project(RandomSeed LANGUAGES C CXX Fortran)
enable_testing()

add_executable(c_seed seed.c)
add_test(NAME "C seed" COMMAND c_seed)

add_executable(cxx_seed seed.cpp)
add_test(NAME "C++ seed" COMMAND cxx_seed)
target_compile_features(cxx_seed PRIVATE cxx_std_11)

add_executable(fortran_seed seed.f90)
add_test(NAME "Fortran seed" COMMAND fortran_seed)
