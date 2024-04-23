include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(othello_setup_dependencies)
  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET Catch3::Catch2WithMain)
    cpmaddpackage(
      NAME
        Catch2
      VERSION
        3.5.3
      GITHUB_REPOSITORY
        "catchorg/Catch2")
  endif()

  if(NOT TARGET ftxui::screen)
    cpmaddpackage(
      NAME
        ftxui
      GITHUB_REPOSITORY
        "ArthurSonzogni/FTXUI"
      GIT_TAG
        "v5.0.0"
      OPTIONS
        "FTXUI_BUILD_DOCS OFF"
        "FTXUI_BUILD_EXAMPLES OFF")
  endif()

endfunction()
