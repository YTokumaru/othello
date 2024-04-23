#include <ftxui/component/screen_interactive.hpp>
#include <othello/board.hpp>
#include <othello/rendering.hpp>


int main()
{
  Screen_State screen_state = Title;
  const othello::Board board;

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  while (screen_state != Exit) {
    switch (screen_state) {
    case Title:
      screen_state = titleRenderer(screen);
      break;
    case Game:
      screen_state = boardRenderer(screen, board);
      break;
    case Exit:
      break;
    }
  }
  return 0;
}
