cmake_minimum_required(VERSION 3.19...3.22)
project(RandomSeed LANGUAGES C CXX Fortran)
enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

add_executable(c_seed seed.c)
add_test(NAME "C seed" COMMAND c_seed)

add_executable(cxx_seed seed.cpp)
add_test(NAME "C++ seed" COMMAND cxx_seed)
target_compile_features(cxx_seed PRIVATE cxx_std_11)

add_executable(fortran_seed seed.f90)
add_test(NAME "Fortran seed" COMMAND fortran_seed)

set_tests_properties("C seed" "C++ seed" "Fortran seed" PROPERTIES TIMEOUT 5)

find_package(Python COMPONENTS Interpreter)
if(Python_FOUND)
  add_test(NAME "Python seed"
  COMMAND Python::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/seed.py
  )
  set_tests_properties("Python seed" PROPERTIES TIMEOUT 5)
endif()

find_package(Matlab COMPONENTS MAIN_PROGRAM)
if(Matlab_FOUND)
  add_test(NAME "Matlab seed"
  COMMAND ${Matlab_MAIN_PROGRAM} -batch seed
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_tests_properties("Matlab seed" PROPERTIES TIMEOUT 60)
endif()

find_package(Octave COMPONENTS Interpreter)
if(Octave_FOUND)
  add_test(NAME "Octave seed"
  COMMAND Octave::Interpreter --eval seed_octave
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()
