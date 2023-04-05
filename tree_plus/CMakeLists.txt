cmake_minimum_required (VERSION 3.5)

project(BPlusTreeLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../container
  ${CMAKE_CURRENT_SOURCE_DIR}/../storage
)

add_library(BPlusTreeLibrary STATIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/b_plus_tree.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/b_plus_tree.h
  ${CMAKE_CURRENT_SOURCE_DIR}/b_plus_tree.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/BPTNode.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/BPTNode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/BPTNode.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/../container/container.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/../container/container.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../storage/storage.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/../storage/storage.h
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
