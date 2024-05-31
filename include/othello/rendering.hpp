#ifndef RENDERING_HPP
#define RENDERING_HPP
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <othello/board.hpp>


const int CANVAS_WIDTH = 160; /**< The width of the board when displayed to console */
const int CANVAS_HEIGHT = 160; /**< The height of the board when displayed to console */

/**
 * The states of screens the game can have
 */
enum Screen_State { Title, Game, Exit };

/**
 * @brief Creates the canvas object of the othello board
 * @param board The board to create the board canvas for
 * @param mouse_x The x coordinate of the mouse
 * @param mouse_y The y coordinate of the mouse
 */
ftxui::Canvas boardCanvas(othello::Board &board, int mouse_x, int mouse_y);

/**
 * @brief Translates canvas coordinate (coordinate on the console) to coordinate of othello board
 * @return Tuple of the coordinate of the board
 */
std::tuple<std::size_t, std::size_t> coord2count(int x_coor, int y_coor);

/**
 * @brief Translated the coordinate of the othello board to console coordinate
 * @return Tuple of the coordinate
 * @note
 * The coordinate returned by the function will be the center coordinate of
 * the given tile. E.g. passing (0,0) will return the center coordinate of the
 * tile located in the upper most left corner. Likewise, passing (7,7) will
 * return the center coordinate of the bottom left corner tile.
 */
std::tuple<int, int> count2coord(std::size_t x_cnt, std::size_t y_cnt);

/**
 * @brief Returns the title logo
 * @return The title logo
 */
ftxui::Element titleLogo();

/**
 * @brief The renderer of the board with mouse and keyboard interaction
 * @param screen ftxui screen object
 * @param board The board to render
 * @return The renderer of the board
 */
Screen_State boardRenderer(ftxui::ScreenInteractive &screen, othello::Board &board);

/**
 * @brief The title renderer
 * @param screen ftxui screen object
 * @return Renderer for the title screen with title logo and buttons
 */
Screen_State titleRenderer(ftxui::ScreenInteractive &screen);
#endif// !RENDERING_HPP
