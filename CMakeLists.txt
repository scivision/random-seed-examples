cmake_minimum_required(VERSION 3.12...3.25)
project(RandomSeed LANGUAGES C CXX Fortran)
enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(c_regex "21238 7719 38")
  set(cxx_regex "1178568022 1273124119 1535857466")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(c_regex "38 7719 21238")
  set(cxx_regex "1178568022 1273124119 1535857466")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(c_regex "21238 7719 38")
  set(cxx_regex "924231285 398764591 209652396")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^Intel")
  set(c_regex "21238 7719 38")
  set(cxx_regex "209652396 398764591 924231285")
else()
  set(c_regex ".*")
  set(cxx_regex ".*")
endif()

if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
  set(fortran_regex "0.471078 0.117346 0.884884")
elseif(CMAKE_Fortran_COMPILER_ID MATCHES "^Intel")
  set(fortran_regex "0.000000 0.025480 0.352516")
else()
  set(fortran_regex ".*")
endif()

add_executable(c_seed seed.c)
add_test(NAME "C" COMMAND c_seed)
set_property(TEST C PROPERTY PASS_REGULAR_EXPRESSION ${c_regex})

add_executable(cxx_seed seed.cpp)
add_test(NAME "Cpp" COMMAND cxx_seed)
target_compile_features(cxx_seed PRIVATE cxx_std_11)
set_property(TEST Cpp PROPERTY PASS_REGULAR_EXPRESSION ${cxx_regex})

add_executable(fortran_seed seed.f90)
add_test(NAME "Fortran" COMMAND fortran_seed)
set_property(TEST Fortran PROPERTY PASS_REGULAR_EXPRESSION ${fortran_regex})

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
find_package(Python COMPONENTS Interpreter)
if(Python_FOUND)
  add_test(NAME "Python"
  COMMAND Python::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/seed.py
  )
  set_property(TEST Python PROPERTY PASS_REGULAR_EXPRESSION "-0.625151[ ]*-0.596945[ ]*0.139097")
endif()
endif()

find_package(Matlab COMPONENTS MAIN_PROGRAM)
if(Matlab_FOUND)
  add_test(NAME "Matlab"
  COMMAND ${Matlab_MAIN_PROGRAM} -batch "seed()"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_property(TEST Matlab PROPERTY PASS_REGULAR_EXPRESSION "0.814724[ ]*0.905792[ ]*0.126987")
endif()

find_package(Octave COMPONENTS Interpreter)
if(Octave_FOUND)
  add_test(NAME "Octave"
  COMMAND Octave::Interpreter --eval "seed()"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_property(TEST Octave PROPERTY PASS_REGULAR_EXPRESSION "0.844422[ ]*0.757954[ ]*0.420572")
endif()

find_program(JULIA_EXECUTABLE NAMES julia)
if(JULIA_EXECUTABLE)
  add_test(NAME "Julia"
  COMMAND ${JULIA_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/seed.jl
  )
  set_property(TEST Julia PROPERTY PASS_REGULAR_EXPRESSION "0.823648 0.910357 0.164566")
endif()
