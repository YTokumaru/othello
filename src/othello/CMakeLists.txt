add_executable(main main.cpp)

target_link_system_libraries(
  main
  PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)
