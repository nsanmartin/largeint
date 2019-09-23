cmake_minimum_required(VERSION 3.2)  
project(lint)  
enable_testing()

include_directories(include)
include_directories(tests/include)

# Can manually add the sources using the set command as follows:  
# set(SOURCES src/*.cpp)
# However, the file(GLOB...) allows for wildcard additions:  
file(GLOB SOURCES "src/*.cpp")

# tests
# gmp for the tests
# find_library(GMP_LIBRARY NAMES gmp gmplib)

file( GLOB TEST_SOURCES "tests/*.cpp")
foreach(testssource ${TEST_SOURCES})
  string( REPLACE ".cpp" "" testnamepath ${testssource} )
  get_filename_component(testname ${testnamepath} NAME)
  add_executable( ${testname} ${testssource} ${SOURCES} )
  target_link_libraries( ${testname} gmp gmpxx )
  add_test(NAME ${testname} COMMAND  ${testname})
endforeach(testssource ${TEST_SOURCES})

add_custom_target(test-random)

file( GLOB TEST_RANDOM_SOURCES "tests-random/*.cpp")
foreach(testssource ${TEST_RANDOM_SOURCES})
  string( REPLACE ".cpp" "" testnamepath ${testssource} )
  get_filename_component(testname ${testnamepath} NAME)
  add_executable( ${testname} ${testssource} ${SOURCES} )
  target_link_libraries( ${testname} gmp gmpxx )
  add_dependencies(test-random ${testname})
  add_custom_command(TARGET test-random POST_BUILD COMMAND ${testname})
endforeach(testssource ${TEST_SOURCES})
