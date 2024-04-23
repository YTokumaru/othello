#ifndef OTHELLO_HPP
#define OTHELLO_HPP
#include <array>
#include <cstddef>
#include <tuple>
#include <vector>


namespace othello {

const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;

enum Color { Empty, Black, White };
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
   * @return EXIT_SUCCESS if successfully placed and board changed, otherwise EXIT_FAILURE
   */
  int place(std::size_t x, std::size_t y, othello::Color color);
  [[nodiscard]] othello::Color at(std::size_t x, std::size_t y) const;
  othello::Color &at(std::size_t x, std::size_t y);

  [[nodiscard]] size_t getTurn() const;

private:
  int edit(std::size_t x, std::size_t y, othello::Color color);
  std::array<std::array<othello::Color, BOARD_WIDTH>, BOARD_HEIGHT> board_state = {};
  std::vector<std::tuple<int, int, othello::Color>> history;
};

}// namespace othello
#endif// !OTHELLO_HPP
