cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(othello CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET othello_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(board_test board_test.cpp)
target_link_libraries(
  board_test
  PRIVATE
          othello::othello_warnings
          othello::othello_options
          othello::board)
target_link_system_libraries(
  board_test
  PRIVATE
    Catch2::Catch2WithMain
)
# Cppcheck and clang-tidy are disabled for tests
set_target_properties(board_test PROPERTIES CXX_CPPCHECK "")
set_target_properties(board_test PROPERTIES CXX_CLANG_TIDY "")

catch_discover_tests(
  board_test
  TEST_PREFIX
  "unittests."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)

