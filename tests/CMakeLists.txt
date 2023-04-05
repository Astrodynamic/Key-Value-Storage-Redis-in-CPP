cmake_minimum_required(VERSION 3.5)
project(TEST VERSION 1.0 LANGUAGES CXX)

#=============================================================== Setup CMake
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS --coverage)
set(CMAKE_EXE_LINKER_FLAGS --coverage)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
  ${CMAKE_SOURCE_DIR}/../binary_tree
  ${CMAKE_SOURCE_DIR}/../container
  ${CMAKE_SOURCE_DIR}/../tree_plus
  ${CMAKE_SOURCE_DIR}/../storage
  ${CMAKE_SOURCE_DIR}/../table
)

enable_testing()

add_executable(
  ${CMAKE_PROJECT_NAME}
  tests.cc
)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/../binary_tree/ ./binary_tree
)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/../tree_plus ./tree_plus
)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/../table ./table
)

target_link_libraries(${CMAKE_PROJECT_NAME}
  GTest::gtest_main
  SelfBalancingBinarySearchTreeLibrary
  BPlusTreeLibrary
  HashTableLibrary
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})

add_custom_target(coverage
  COMMAND lcov -c -d . -o main_coverage.info
  --exclude *_deps* --exclude *include/* --exclude *gtest*
  --exclude *self_balancing_binary_search_tree.cc* --exclude *RBTree.inc*
  --exclude *storage.cc* --exclude *BPTNode* --exclude *b_plus_tree.cc*
  --exclude *hash_table.cc*
  COMMAND genhtml main_coverage.info --output-directory coverage-report
)
