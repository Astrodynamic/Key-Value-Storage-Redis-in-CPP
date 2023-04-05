cmake_minimum_required(VERSION 3.5)

project(Redis VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/binary_tree
  ${CMAKE_SOURCE_DIR}/container
  ${CMAKE_SOURCE_DIR}/tree_plus
  ${CMAKE_SOURCE_DIR}/interface
  ${CMAKE_SOURCE_DIR}/storage
  ${CMAKE_SOURCE_DIR}/table
)

add_executable(
  ${PROJECT_NAME}
  interface/interface.h
  interface/interface.cc
  main.cc
)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/binary_tree
)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/tree_plus
)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/table
)

target_link_libraries(
  ${PROJECT_NAME}
  BPlusTreeLibrary
  HashTableLibrary
  SelfBalancingBinarySearchTreeLibrary
)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.h *.inc)

add_custom_target(
        style
        COMMAND clang-format
        -style=Google
        --verbose
        -n
        ${ALL_SOURCE_FILES}
)

add_custom_target(
        clangformat
        COMMAND clang-format
        -style=Google
        --verbose
        -i
        ${ALL_SOURCE_FILES}
)

add_custom_target(
        cppcheck
        COMMAND cppcheck
        --enable=all
        --inconclusive
        --language=c++
        --std=c++17
        --verbose
        --suppress=cppcheckError
        --suppress=constParametr
        --suppress=useStlAlgorithm
        --suppress=functionStatic
        --suppress=passedByValue
        --suppress=missingReturn
        --suppress=constParameter
        --suppress=operatorEqMissingReturnStatement
        --suppress=postfixOperator
        --suppress=unmatchedSuppression
        --suppress=missingInclude
        --quiet
        ${ALL_SOURCE_FILES}
)
