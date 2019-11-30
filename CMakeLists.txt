cmake_minimum_required(VERSION 3.10)

enable_testing()

# set the project name
project(Boardgame_DSL)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(Parser ${CMAKE_SOURCE_DIR}/src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(Scanner ${CMAKE_SOURCE_DIR}/src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} include)

add_executable(bgcc
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
    src/main.cpp
    src/ast.cpp
    src/builtins.cpp
    src/interpreter.cpp
)

add_test(test ${CMAKE_SOURCE_DIR}/test/test.py)
