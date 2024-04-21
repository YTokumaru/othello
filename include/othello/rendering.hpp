#ifndef RENDERING_HPP
#define RENDERING_HPP
#include <ftxui/dom/canvas.hpp>
#include <othello/board.hpp>


const int CANVAS_WIDTH = 160;
const int CANVAS_HEIGHT = 160;
ftxui::Canvas boardCanvas(othello::Board board, int mouse_x, int mouse_y);
std::tuple<int, int> coord2count(int x_coor, int y_coor);
std::tuple<int, int> count2coord(int x_cnt, int y_cnt);
#endif// !RENDERING_HPP
