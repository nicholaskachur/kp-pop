########################################################################
# These build files provide everything needed to build and run the
# exercises contained in this project.
#
# To build, first create a build directory and the run CMake
#   $ mkdir build
#   $ cmake ..
#   $ make
#
# To run all the programs (as tests), use the `test` target
#   $ make test
#
# To clean the build directory, use the `clean` target
#   $ make clean
#
# Author: Nicholas Kachur <nick.e.kachur@gmail.com>
########################################################################
cmake_minimum_required(VERSION 3.0.0)
project(KP-POP)

find_package(Java REQUIRED)
include(UseJava)

enable_testing()

add_subdirectory(ch1)
add_subdirectory(ch2)

