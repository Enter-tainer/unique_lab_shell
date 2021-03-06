cmake_minimum_required(VERSION 3.15)
project(unique_lab_shell)

find_package(Catch2 REQUIRED)
find_library(readline REQUIRED)
set(CMAKE_CXX_STANDARD 17)

AUX_SOURCE_DIRECTORY(shell SHELL_SOURCE)
AUX_SOURCE_DIRECTORY(parser PARSER_SOURCE)

add_executable(unique_lab_shell main.cpp system_call.h
        readline.h readline.cpp repl.cpp repl.h string_opt.h
        ${SHELL_SOURCE} ${PARSER_SOURCE}
        parser/eval.cpp parser/eval.h shell/export.h)

add_executable(cat bin/cat.cpp)
add_executable(ls bin/ls.cpp)
add_executable(touch bin/touch.cpp)
add_executable(mkdir bin/mkdir.cpp)
add_executable(rm bin/rm.cpp)
add_executable(cp bin/cp.cpp)
add_executable(ln bin/ln.cpp)
add_executable(more bin/more.cpp)
add_executable(xargs bin/xargs.cpp ${SHELL_SOURCE})
target_link_libraries(unique_lab_shell readline)

add_executable(string_opt_test spec/string_opt_test.cpp)
target_link_libraries(string_opt_test Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(string_opt_test)