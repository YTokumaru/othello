# Enable cache if available
function(othello_enable_cache)
  set(CACHE_OPTION
      "ccache"
      CACHE STRING "Compiler cache to be used")
  set(CACHE_OPTION_VALUES "ccache" "sccache")
  set_property(CACHE CACHE_OPTION PROPERTY STRINGS ${CACHE_OPTION_VALUES})
  list(
    FIND
    CACHE_OPTION_VALUES
    ${CACHE_OPTION}
    CACHE_OPTION_INDEX)

  if(${CACHE_OPTION_INDEX} EQUAL -1)
    message(
      STATUS
        "Using custom compiler cache system: '${CACHE_OPTION}', explicitly supported entries are ${CACHE_OPTION_VALUES}"
    )
  endif()

  find_program(CACHE_BINARY NAMES ${CACHE_OPTION_VALUES})
  if(CACHE_BINARY)
    get_binary_version(CACHE_BINARY_VERSION ${CACHE_BINARY})
    message(STATUS "${CACHE_BINARY} ${CACHE_BINARY_VERSION} found. Using it as compiler cache")
    set(CMAKE_CXX_COMPILER_LAUNCHER
        ${CACHE_BINARY}
        CACHE FILEPATH "CXX compiler cache used")
    set(CMAKE_C_COMPILER_LAUNCHER
        ${CACHE_BINARY}
        CACHE FILEPATH "C compiler cache used")
  else()
    message(WARNING "${CACHE_OPTION} is enabled but was not found. Not using it")
  endif()
endfunction()
