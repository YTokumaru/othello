#ifndef OTHELLO_HPP
#include <array>
#include <tuple>
#include <vector>


namespace othello {

unsigned const int BOARD_HEIGHT = 8;
unsigned const int BOARD_WIDTH = 8;

enum Color { Empty, Black, White };

class Board
{
public:
  Board();
  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board();

  int edit(int x, int y, othello::Color color);
  int place(int x, int y, othello::Color color);
  [[nodiscard]] othello::Color at(int x, int y) const;
  othello::Color &at(int x, int y);

private:
  std::array<std::array<othello::Color, BOARD_WIDTH>, BOARD_HEIGHT> board_state = {};
  std::vector<std::tuple<int, int, othello::Color>> history;
};

}// namespace othello
#endif// !OTHELLO_HPP
