add_subdirectory(sample_library)
add_subdirectory(ftxui_sample)

include(GenerateExportHeader)

## ---- Othello ---- ##

add_executable(othello othello.cpp)
target_link_libraries(othello PRIVATE game_state othello_options othello_warnings)
target_link_system_libraries(
  othello
  PRIVATE
          CLI11::CLI11
          fmt::fmt
          spdlog::spdlog
          lefticus::tools
          ftxui::screen
          ftxui::dom
          ftxui::component)

## ---- Game State ---- ##

add_library(game_state game_state.cpp)
target_link_libraries(game_state PRIVATE othello_options othello_warnings)
target_link_system_libraries(
  game_state
  PRIVATE
          CLI11::CLI11
          fmt::fmt
          spdlog::spdlog
          lefticus::tools
          ftxui::screen
          ftxui::dom
          ftxui::component)
target_include_directories(game_state ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_compile_features(game_state PUBLIC cxx_std_20)
set_target_properties(
  game_state
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)
generate_export_header(game_state EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/game_state.hpp)
if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(game_state PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
