#include <ftxui/component/component.hpp>// for Slider
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>// for text, border
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <functional>
#include <othello/board.hpp>
#include <utility>


std::function<void(ftxui::Pixel &)> setColor(ftxui::Color foreground, ftxui::Color backgroud)
{
  return [foreground, backgroud](ftxui::Pixel &pixel) {
    pixel.foreground_color = foreground;
    pixel.background_color = backgroud;
  };
}

ftxui::Canvas boardCanvas(int mouse_x, int mouse_y)
{

  const int board_size = 8;
  const int canvas_size = 160;
  const int radius = 8;

  const ftxui::Color board_color = ftxui::Color::Green;

  auto mycanvas = ftxui::Canvas(canvas_size, canvas_size);
  // Color the background
  for (int x_coor = 0; x_coor < canvas_size; x_coor++) {
    for (int y_coor = 0; y_coor < canvas_size; y_coor++) {
      mycanvas.DrawBlock(
        x_coor, y_coor, true, [board_color](ftxui::Pixel &pixel) { pixel.foreground_color = board_color; });
    }
  }
  // Draw the pieces if the mouse is inside
  for (int x_cnt = 0; x_cnt < board_size; x_cnt++) {
    for (int y_cnt = 0; y_cnt < board_size; y_cnt++) {
      if ((canvas_size / board_size) * x_cnt <= mouse_x && mouse_x < (canvas_size / board_size) * (x_cnt + 1)
          && (canvas_size / board_size) * y_cnt <= mouse_y && mouse_y < (canvas_size / board_size) * (y_cnt + 1)) {
        mycanvas.DrawPointCircleFilled((canvas_size / board_size) * x_cnt + (canvas_size / board_size) / 2,
          (canvas_size / board_size) * y_cnt + (canvas_size / board_size) / 2,
          radius,
          setColor(ftxui::Color::Black, board_color));
      }
    }
  }
  return mycanvas;
}

int main()
{
  int mouse_x = 0;
  int mouse_y = 0;
  auto screen = ftxui::ScreenInteractive::FitComponent();
  auto board_component = ftxui::Renderer([&]() { return ftxui::canvas(std::move(boardCanvas(mouse_x, mouse_y))); })
                         | ftxui::CatchEvent([&](ftxui::Event event) {// Mouse handling
                             if (event.is_mouse()) {
                               mouse_x = event.mouse().x * 2;
                               mouse_y = event.mouse().y * 4;
                               if (event.mouse().motion == ftxui::Mouse::Motion::Pressed) { screen.Exit(); }
                             }
                             return false;
                           });
  auto component_renderer = ftxui::Renderer(board_component, [&] { return board_component->Render(); });
  screen.Loop(component_renderer);
  return 0;
}
