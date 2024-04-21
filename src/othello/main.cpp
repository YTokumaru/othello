#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <functional>
#include <othello/board.hpp>


std::function<void(ftxui::Pixel &)> setColor(ftxui::Color foreground, ftxui::Color backgroud)
{
  return [foreground, backgroud](ftxui::Pixel &pixel) {
    pixel.foreground_color = foreground;
    pixel.background_color = backgroud;
  };
}

ftxui::Canvas boardCanvas(othello::Board board, int mouse_x, int mouse_y)
{

  const int BOARD_SIZE = 8;
  const int CANVAS_SIZE = 160;
  const int RADIUS = 8;

  const ftxui::Color BOARD_COLOR = ftxui::Color::Green;
  auto mycanvas = ftxui::Canvas(CANVAS_SIZE, CANVAS_SIZE);
  // Color the background
  for (int x_coor = 0; x_coor < CANVAS_SIZE; x_coor++) {
    for (int y_coor = 0; y_coor < CANVAS_SIZE; y_coor++) {
      mycanvas.DrawBlock(
        x_coor, y_coor, true, [BOARD_COLOR](ftxui::Pixel &pixel) { pixel.foreground_color = BOARD_COLOR; });
    }
  }
  // Draw the pieces if the mouse is inside
  for (int x_cnt = 0; x_cnt < BOARD_SIZE; x_cnt++) {
    for (int y_cnt = 0; y_cnt < BOARD_SIZE; y_cnt++) {
      if ((CANVAS_SIZE / BOARD_SIZE) * x_cnt <= mouse_x && mouse_x < (CANVAS_SIZE / BOARD_SIZE) * (x_cnt + 1)
          && (CANVAS_SIZE / BOARD_SIZE) * y_cnt <= mouse_y && mouse_y < (CANVAS_SIZE / BOARD_SIZE) * (y_cnt + 1)) {
        mycanvas.DrawPointCircleFilled((CANVAS_SIZE / BOARD_SIZE) * x_cnt + (CANVAS_SIZE / BOARD_SIZE) / 2,
          (CANVAS_SIZE / BOARD_SIZE) * y_cnt + (CANVAS_SIZE / BOARD_SIZE) / 2,
          RADIUS,
          setColor(ftxui::Color::Black, BOARD_COLOR));
      }
    }
  }

  // draw the board
  for (int x_cnt = 0; x_cnt < BOARD_SIZE; x_cnt++) {
    for (int y_cnt = 0; y_cnt < BOARD_SIZE; y_cnt++) {
      switch (board.at(x_cnt, y_cnt)) {
      case othello::White:
        mycanvas.DrawPointCircleFilled((CANVAS_SIZE / BOARD_SIZE) * x_cnt + (CANVAS_SIZE / BOARD_SIZE) / 2,
          (CANVAS_SIZE / BOARD_SIZE) * y_cnt + (CANVAS_SIZE / BOARD_SIZE) / 2,
          RADIUS,
          setColor(ftxui::Color::White, BOARD_COLOR));
        break;
      case othello::Black:
        mycanvas.DrawPointCircleFilled((CANVAS_SIZE / BOARD_SIZE) * x_cnt + (CANVAS_SIZE / BOARD_SIZE) / 2,
          (CANVAS_SIZE / BOARD_SIZE) * y_cnt + (CANVAS_SIZE / BOARD_SIZE) / 2,
          RADIUS,
          setColor(ftxui::Color::Black, BOARD_COLOR));
        break;
      default:
        break;
      }
    }
  }
  return mycanvas;
}

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
                               if (event.mouse().motion == ftxui::Mouse::Motion::Pressed) { screen.Exit(); }
                             }
                             return false;
                           });
  auto component_renderer = ftxui::Renderer(board_component, [&] { return board_component->Render(); });
  screen.Loop(component_renderer);
  return 0;
}
