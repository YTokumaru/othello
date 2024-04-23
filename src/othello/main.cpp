#include <ftxui/component/screen_interactive.hpp>
#include <othello/board.hpp>
#include <othello/rendering.hpp>

int main()
{
  const othello::Board board;

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  if (titleRenderer(screen) == 0) { boardRenderer(screen, board); }
  return 0;
}
