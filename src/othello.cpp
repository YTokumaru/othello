#include <game_state.hpp>
#include <iostream>

int main()
{
  auto screen = ftxui::ScreenInteractive::Fullscreen();
//   GameState state = GameState::TITLE;
  TitleScreen titleScreen(
    screen,
    [&]() { std::cout << "Start selected\n"; },
    [&]() { std::cout << "Setting selected\n"; },
    [&]() { std::cout << "Quit selected\n"; });

  titleScreen.display();
  return EXIT_SUCCESS;
}