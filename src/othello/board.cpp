#include <array>
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


size_t Board::getTurn() const { return history.size(); }

int Board::place(int x, int y, Color color)
{
  bool place_success = false;
  // The tile we are trying to place must be empty
  if (at(x, y) != Empty) { return EXIT_FAILURE; }

  // Check all directions
  const int DIRECTION_CNT = 8;
  const std::array<std::array<short, 2>, DIRECTION_CNT> directions = { { { { 1, 0 } },
    { { 1, 1 } },
    { { 0, 1 } },
    { { -1, 1 } },
    { { -1, 0 } },
    { { -1, -1 } },
    { { 0, -1 } },
    { { 1, -1 } } } };
  for (std::array<short, 2> direction : directions) {
    // Check if a specific direction can be changed
    bool exists_opposite = false;
    for (int check_x = x + direction.at(0), check_y = y + direction.at(1);
         0 <= check_x && check_x < BOARD_WIDTH && 0 <= check_y && check_y < BOARD_HEIGHT;
         check_x += direction.at(0), check_y += direction.at(1)) {
      if (at(check_x, check_y) == Empty) { break; }
      if (at(check_x, check_y) == !color) {
        exists_opposite = true;
        continue;
      }
      if (exists_opposite && (at(check_x, check_y) == color)) {
        // The opposing color is sandwiched by ours
        for (int change_x = x, change_y = y; change_x != check_x || change_y != check_y;
             change_x += direction.at(0), change_y += direction.at(1)) {
          edit(change_x, change_y, color);
        }
        place_success = true;
      }
    }
  }
  if (place_success) {
    history.emplace_back(x, y, color);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
