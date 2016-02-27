########################################################################
# Build files for kp-pop/ch2.
#
# Author: Nicholas Kachur <nick.e.kachur@gmail.com>
########################################################################

add_executable( ex2-1 ex2-1.c )
add_test( ex2-1 ${CMAKE_CURRENT_BINARY_DIR}/ex2-1 1000 100 )

add_jar( ex2-2 Ex2_2.java )
get_target_property( ex2-2_jar ex2-2 JAR_FILE )
add_test( ex2-2 ${Java_JAVA_EXECUTABLE} -cp ${ex2-2_jar} Ex2_2 )

add_executable( ex2-3 ex2-3.c )
add_test( ex2-3 ${CMAKE_CURRENT_BINARY_DIR}/ex2-3 100000 100 )

add_executable( ex2-4 ex2-4.c )
add_test( ex2-4 ${CMAKE_CURRENT_BINARY_DIR}/ex2-4 1000 100 )

