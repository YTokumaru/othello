#ifndef OTHELLO_HPP
#define OTHELLO_HPP
#include <array>
#include <cstddef>
#include <tuple>
#include <vector>


namespace othello {

const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;

/**
 * @brief Returns true if the given board coordiate is in bounds
 * @param x The x coordinate
 * @param y The y coordinate
 * @return True if it is inbonds, False otherwise
 */
inline bool isInbounds(int x, int y) { return (0 <= x && x < BOARD_WIDTH) && (0 <= y && y < BOARD_HEIGHT); }

enum Color { Empty, Black, White };

/**
 * @brief Returns the opposite color
 * @param color The color to invert
 * @return The opposite color
 */
inline Color operator!(Color color)
{
  switch (color) {
  case Black:
    return White;
  case White:
    return Black;
  default:
    return Empty;
  }
}

/**
 * Board class
 */
class Board
{
public:
  Board();
  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board() = default;

  /**
   * @brief Changes the board by a piece on (x,y)
   * @param x The x coordinate on the board
   * @param y The y coordinate on the board
   * @return EXIT_SUCCESS if successfully placed and board changed, otherwise EXIT_FAILURE
   */
  int place(std::size_t x, std::size_t y, othello::Color color);

  /**
   * @brief Returns the color at the given coordinate
   * @param x The x coordinate
   * @param t The y coordinate
   * @return The color of the board
   */
  [[nodiscard]] othello::Color at(std::size_t x, std::size_t y) const;
  othello::Color &at(std::size_t x, std::size_t y);

  /**
   * @brief Return the number of the turns made
   * @return The numbers of turns made
   */
  [[nodiscard]] size_t getTurn() const;

private:
  /**
   * @brief Edit the board at the coordinate (x,y)
   * @param x The x coordinate
   * @param y The y coordinate
   * @param color The color to place
   * @return EXIT_SUCCESS
   */
  int edit(std::size_t x, std::size_t y, othello::Color color);

  std::array<std::array<othello::Color, BOARD_WIDTH>, BOARD_HEIGHT>
    board_state = {}; /**< The current state of the board */

  std::vector<std::tuple<int, int, othello::Color>> history; /**< The history of the board */
};

}// namespace othello
#endif// !OTHELLO_HPP
