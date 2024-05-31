include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(othello_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(othello_setup_options)
  option(othello_ENABLE_HARDENING "Enable hardening" ON)
  option(othello_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    othello_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    othello_ENABLE_HARDENING
    OFF)

  othello_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR othello_PACKAGING_MAINTAINER_MODE OR CMAKE_BUILD_TYPE MATCHES "RELEASE")
    option(othello_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(othello_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(othello_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(othello_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(othello_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(othello_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(othello_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(othello_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(othello_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(othello_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(othello_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(othello_ENABLE_PCH "Enable precompiled headers" OFF)
    option(othello_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(othello_ENABLE_IPO "Enable IPO/LTO" ON)
    option(othello_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(othello_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(othello_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(othello_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(othello_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(othello_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(othello_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(othello_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(othello_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(othello_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(othello_ENABLE_PCH "Enable precompiled headers" OFF)
    option(othello_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      othello_ENABLE_IPO
      othello_WARNINGS_AS_ERRORS
      othello_ENABLE_USER_LINKER
      othello_ENABLE_SANITIZER_ADDRESS
      othello_ENABLE_SANITIZER_LEAK
      othello_ENABLE_SANITIZER_UNDEFINED
      othello_ENABLE_SANITIZER_THREAD
      othello_ENABLE_SANITIZER_MEMORY
      othello_ENABLE_UNITY_BUILD
      othello_ENABLE_CLANG_TIDY
      othello_ENABLE_CPPCHECK
      othello_ENABLE_COVERAGE
      othello_ENABLE_PCH
      othello_ENABLE_CACHE)
  endif()

  othello_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (othello_ENABLE_SANITIZER_ADDRESS OR othello_ENABLE_SANITIZER_THREAD OR othello_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(othello_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(othello_global_options)
  if(othello_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    othello_enable_ipo()
  endif()

  othello_supports_sanitizers()

  if(othello_ENABLE_HARDENING AND othello_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR othello_ENABLE_SANITIZER_UNDEFINED
       OR othello_ENABLE_SANITIZER_ADDRESS
       OR othello_ENABLE_SANITIZER_THREAD
       OR othello_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${othello_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${othello_ENABLE_SANITIZER_UNDEFINED}")
    othello_enable_hardening(othello_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(othello_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(othello_warnings INTERFACE)
  add_library(othello_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  othello_set_project_warnings(
    othello_warnings
    ${othello_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(othello_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(othello_options)
  endif()

  include(cmake/Sanitizers.cmake)
  othello_enable_sanitizers(
    othello_options
    ${othello_ENABLE_SANITIZER_ADDRESS}
    ${othello_ENABLE_SANITIZER_LEAK}
    ${othello_ENABLE_SANITIZER_UNDEFINED}
    ${othello_ENABLE_SANITIZER_THREAD}
    ${othello_ENABLE_SANITIZER_MEMORY})

  set_target_properties(othello_options PROPERTIES UNITY_BUILD ${othello_ENABLE_UNITY_BUILD})

  if(othello_ENABLE_PCH)
    target_precompile_headers(
      othello_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(othello_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    othello_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(othello_ENABLE_CLANG_TIDY)
    othello_enable_clang_tidy(othello_options ${othello_WARNINGS_AS_ERRORS})
  endif()

  if(othello_ENABLE_CPPCHECK)
    othello_enable_cppcheck(${othello_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(othello_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    othello_enable_coverage(othello_options)
  endif()

  if(othello_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(othello_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(othello_ENABLE_HARDENING AND NOT othello_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR othello_ENABLE_SANITIZER_UNDEFINED
       OR othello_ENABLE_SANITIZER_ADDRESS
       OR othello_ENABLE_SANITIZER_THREAD
       OR othello_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    othello_enable_hardening(othello_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
