#include <cstddef>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <functional>
#include <othello/board.hpp>
#include <othello/rendering.hpp>
#include <string>
#include <tuple>
#include <vector>


std::function<void(ftxui::Pixel &)> setColor(ftxui::Color foreground, ftxui::Color backgroud)
{
  return [foreground, backgroud](ftxui::Pixel &pixel) {
    pixel.foreground_color = foreground;
    pixel.background_color = backgroud;
  };
}

std::tuple<std::size_t, std::size_t> coord2count(int x_coor, int y_coor)
{
  return { (x_coor * othello::BOARD_WIDTH / CANVAS_WIDTH), (y_coor * othello::BOARD_HEIGHT / CANVAS_HEIGHT) };
}

std::tuple<int, int> count2coord(std::size_t x_cnt, std::size_t y_cnt)
{
  const int tile_width = CANVAS_WIDTH / othello::BOARD_WIDTH;
  const int tile_height = CANVAS_HEIGHT / othello::BOARD_HEIGHT;
  return { x_cnt * tile_width + (tile_width / 2), y_cnt * tile_height + (tile_height / 2) };
}

ftxui::Canvas boardCanvas(othello::Board board, int mouse_x, int mouse_y)
{
  const int RADIUS = 8;
  const ftxui::Color BOARD_COLOR = ftxui::Color::Green;
  auto mycanvas = ftxui::Canvas(CANVAS_WIDTH, CANVAS_HEIGHT);

  // Color the background
  for (int x_coor = 0; x_coor < CANVAS_WIDTH; x_coor++) {
    for (int y_coor = 0; y_coor < CANVAS_HEIGHT; y_coor++) {
      mycanvas.DrawBlock(
        x_coor, y_coor, true, [BOARD_COLOR](ftxui::Pixel &pixel) { pixel.foreground_color = BOARD_COLOR; });
    }
  }

  // Draw the piece if the mouse is inside
  auto [mouse_x_cnt, mouse_y_cnt] = coord2count(mouse_x, mouse_y);
  auto [mouse_tile_x, mouse_tile_y] = count2coord(mouse_x_cnt, mouse_y_cnt);
  mycanvas.DrawPointCircle(mouse_tile_x,
    mouse_tile_y,
    RADIUS,
    setColor(board.getTurn() % 2 == 0 ? ftxui::Color::Black : ftxui::Color::White, BOARD_COLOR));

  // draw the board
  for (std::size_t x_cnt = 0; x_cnt < othello::BOARD_WIDTH; x_cnt++) {
    for (std::size_t y_cnt = 0; y_cnt < othello::BOARD_HEIGHT; y_cnt++) {
      auto [center_x, center_y] = count2coord(x_cnt, y_cnt);
      switch (board.at(x_cnt, y_cnt)) {
      case othello::White:
        mycanvas.DrawPointCircleFilled(center_x, center_y, RADIUS, setColor(ftxui::Color::White, BOARD_COLOR));
        break;
      case othello::Black:
        mycanvas.DrawPointCircleFilled(center_x, center_y, RADIUS, setColor(ftxui::Color::Black, BOARD_COLOR));
        break;
      default:
        break;
      }
    }
  }
  return mycanvas;
}

Screen_State boardRenderer(ftxui::ScreenInteractive &screen, othello::Board board)
{
  int mouse_x = 0;
  int mouse_y = 0;
  auto myscreen = ftxui::Renderer([&]() { return ftxui::canvas(boardCanvas(board, mouse_x, mouse_y)); })
                  | ftxui::CatchEvent([&](ftxui::Event event) {// Mouse handling
                      if (event.is_mouse()) {
                        mouse_x = event.mouse().x * 2;
                        mouse_y = event.mouse().y * 4;
                        if (event.mouse().motion == ftxui::Mouse::Motion::Pressed) {
                          auto [x_cnt, y_cnt] = coord2count(mouse_x, mouse_y);
                          if (board.getTurn() % 2 == 0) {
                            board.place(x_cnt, y_cnt, othello::Black);
                          } else {
                            board.place(x_cnt, y_cnt, othello::White);
                          }
                        }
                      }
                      return false;
                    });
  auto component_renderer = ftxui::Renderer(myscreen, [&] { return myscreen->Render(); });
  screen.Loop(component_renderer);
  return Exit;
}

ftxui::Element titleLogo()
{
  return ftxui::vbox(ftxui::text(" ██████╗ ████████╗██╗  ██╗███████╗██╗     ██╗      ██████╗ "),
    ftxui::text("██╔═══██╗╚══██╔══╝██║  ██║██╔════╝██║     ██║     ██╔═══██╗"),
    ftxui::text("██║   ██║   ██║   ███████║█████╗  ██║     ██║     ██║   ██║"),
    ftxui::text("██║   ██║   ██║   ██╔══██║██╔══╝  ██║     ██║     ██║   ██║"),
    ftxui::text("╚██████╔╝   ██║   ██║  ██║███████╗███████╗███████╗╚██████╔╝"),
    ftxui::text(" ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ "));
}

Screen_State titleRenderer(ftxui::ScreenInteractive &screen)
{
  const std::vector<std::string> entries = { "Start", "Quit" };

  int selected = 0;

  ftxui::MenuOption option;
  option.on_enter = screen.ExitLoopClosure();

  auto menu = ftxui::Menu(&entries, &selected, option);

  auto title_screen = ftxui::Renderer(menu, [&] {
    return ftxui::hbox(
      ftxui::filler(), ftxui::vbox(ftxui::filler(), titleLogo(), menu->Render(), ftxui::filler()), ftxui::filler());
  });

  screen.Loop(title_screen);
  return selected == 0 ? Game : Exit;
}
