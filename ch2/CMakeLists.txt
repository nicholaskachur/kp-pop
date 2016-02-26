########################################################################
# Build files for kp-pop/ch2.
#
# Author: Nicholas Kachur <nick.e.kachur@gmail.com>
########################################################################

add_executable( ex2-1 ex2-1.c )
add_test( ex2-1 ${CMAKE_CURRENT_BINARY_DIR}/ex2-1 1000 100 )
