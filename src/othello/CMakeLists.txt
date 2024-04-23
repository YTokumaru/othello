include(GenerateExportHeader)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE othello_options othello_warnings)
target_link_libraries(
  main
  PRIVATE
    othello::board
    othello::rendering
)
target_link_system_libraries(
  main
  PRIVATE
    ftxui::component
)


add_library(board board.cpp)
add_library(othello::board ALIAS board)
target_link_libraries(board PRIVATE othello_options othello_warnings)
target_include_directories(board ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_compile_features(board PUBLIC cxx_std_20)
set_target_properties(
  board
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)
# generate_export_header(board EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/othello/board.hpp)
if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(board PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()

add_library(rendering rendering.cpp)
add_library(othello::rendering ALIAS rendering)
target_link_libraries(rendering PRIVATE othello_options othello_warnings)
target_link_libraries(
  rendering
  PRIVATE
  othello::board
)
target_link_system_libraries(
  rendering
  PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)
target_include_directories(rendering ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_compile_features(rendering PUBLIC cxx_std_20)
set_target_properties(
  rendering
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)
# generate_export_header(rendering EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/othello/rendering.hpp)
if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(rendering PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
