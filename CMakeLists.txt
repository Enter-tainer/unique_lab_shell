cmake_minimum_required(VERSION 3.15)
project(unique_lab_shell)

find_package(Catch2 REQUIRED)
find_library(readline REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(unique_lab_shell main.cpp system_call.h readline.h readline.cpp)


target_link_libraries(unique_lab_shell readline)

#add_executable(fibheap_test fibheap_test.cpp)
#target_link_libraries(llrb_test Catch2::Catch2)
#target_link_libraries(fibheap_test Catch2::Catch2)
#include(CTest)
#include(Catch)
#catch_discover_tests(llrb_test fibheap_test)