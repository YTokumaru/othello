#ifndef RENDERING_HPP
#define RENDERING_HPP
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <othello/board.hpp>


const int CANVAS_WIDTH = 160;
const int CANVAS_HEIGHT = 160;
enum Screen_State { Title, Game, Exit };
ftxui::Canvas boardCanvas(othello::Board board, int mouse_x, int mouse_y);
std::tuple<int, int> coord2count(int x_coor, int y_coor);
std::tuple<int, int> count2coord(int x_cnt, int y_cnt);
ftxui::Element titleLogo();
Screen_State boardRenderer(ftxui::ScreenInteractive &screen, othello::Board board);
Screen_State titleRenderer(ftxui::ScreenInteractive &screen);
#endif// !RENDERING_HPP
