#include <cstdlib>
#include <othello/board.hpp>


using namespace othello;

Board::Board()
{
  at(BOARD_WIDTH / 2, BOARD_HEIGHT / 2) = Black;
  at(BOARD_WIDTH / 2 - 1, BOARD_HEIGHT / 2 - 1) = Black;
  at(BOARD_WIDTH / 2 - 1, BOARD_HEIGHT / 2) = White;
  at(BOARD_WIDTH / 2, BOARD_WIDTH / 2 - 1) = White;
}

int Board::edit(int x, int y, Color color)
{
  board_state.at(y).at(x) = color;
  return EXIT_SUCCESS;
}

Color Board::at(int x, int y) const { return board_state.at(y).at(x); }

Color &Board::at(int x, int y) { return board_state.at(y).at(x); }

int Board::place(int x, int y, Color color)
{
  if (this->at(x, y) != Empty) { return EXIT_FAILURE; }
  return EXIT_SUCCESS;
}
