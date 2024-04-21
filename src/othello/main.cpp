#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <othello/board.hpp>
#include <othello/rendering.hpp>

int main()
{
  othello::Board board;
  board.edit(1, 2, othello::White);
  board.place(3, 2, othello::White);

  int mouse_x = 0;
  int mouse_y = 0;
  auto screen = ftxui::ScreenInteractive::FitComponent();
  auto board_component = ftxui::Renderer([&]() { return ftxui::canvas(boardCanvas(board, mouse_x, mouse_y)); })
                         | ftxui::CatchEvent([&](ftxui::Event event) {// Mouse handling
                             if (event.is_mouse()) {
                               mouse_x = event.mouse().x * 2;
                               mouse_y = event.mouse().y * 4;
                               if (event.mouse().motion == ftxui::Mouse::Motion::Pressed) {
                                 auto [x_cnt, y_cnt] = coord2count(mouse_x, mouse_y);
                                 board.place(x_cnt, y_cnt, othello::Black);
                               }
                             }
                             return false;
                           });
  auto component_renderer = ftxui::Renderer(board_component, [&] { return board_component->Render(); });
  screen.Loop(component_renderer);
  return 0;
}
