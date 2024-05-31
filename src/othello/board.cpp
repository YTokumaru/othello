#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <othello/board.hpp>

using namespace othello;

Board::Board()
{
  at(BOARD_WIDTH / 2, BOARD_HEIGHT / 2) = Black;
  at(BOARD_WIDTH / 2 - 1, BOARD_HEIGHT / 2 - 1) = Black;
  at(BOARD_WIDTH / 2 - 1, BOARD_HEIGHT / 2) = White;
  at(BOARD_WIDTH / 2, BOARD_WIDTH / 2 - 1) = White;
  history.emplace_back(board_state);
}

int Board::edit(std::size_t x, std::size_t y, Color color)
{
  board_state.at(y).at(x) = color;
  return EXIT_SUCCESS;
}

void Board::noPlace() { history.emplace_back(board_state); }

Color Board::at(std::size_t x, std::size_t y) const { return board_state.at(y).at(x); }

Color &Board::at(std::size_t x, std::size_t y) { return board_state.at(y).at(x); }

int Board::revert()
{
  if (history.size() < 2) { return EXIT_FAILURE; }
  history.pop_back();
  board_state = history.back();
  return EXIT_SUCCESS;
}

int Board::revert(std::size_t count)
{
  for (std::size_t i = 0; i < count; i++) {
    if (revert() == EXIT_FAILURE) { return EXIT_FAILURE; }
  }
  return EXIT_SUCCESS;
}

bool Board::isPlacable(othello::Color color) const
{
  for (std::size_t x_coor = 0; x_coor < BOARD_WIDTH; x_coor++) {
    for (std::size_t y_coor = 0; y_coor < BOARD_HEIGHT; y_coor++) {
      if (isPlacable(x_coor, y_coor, color)) { return true; }
    }
  }
  return false;
}

bool Board::isPlacable(std::size_t x, std::size_t y, othello::Color color) const
{
  // Check all directions
  const int DIRECTION_CNT = 8;
  const std::array<std::array<std::ptrdiff_t, 2>, DIRECTION_CNT> directions = { { { { 1, 0 } },
    { { 1, 1 } },
    { { 0, 1 } },
    { { -1, 1 } },
    { { -1, 0 } },
    { { -1, -1 } },
    { { 0, -1 } },
    { { 1, -1 } } } };
  if (std::ranges::any_of(directions, [&](auto direction) { return checkDirection(x, y, direction, color) > 0; })) {
    return true;
  };
  return false;
}

size_t Board::getTurn() const { return history.size(); }

int Board::checkDirection(std::size_t x,
  std::size_t y,
  std::array<std::ptrdiff_t, 2> direction,
  othello::Color color) const
{
  // The tile we are trying to place must be empty
  if (at(x, y) != Empty) { return 0; }

  bool exists_opposite = false;

  int counter = 0;// The number of times we steped into the direction

  // Step by 1 in the direction (note that the iteration starts from the adjacent tile)
  for (std::ptrdiff_t check_x = static_cast<std::ptrdiff_t>(x) + direction.at(0),
                      check_y = static_cast<std::ptrdiff_t>(y) + direction.at(1);
       0 <= check_x && check_x < BOARD_WIDTH && 0 <= check_y && check_y < BOARD_HEIGHT;
       check_x += direction.at(0), check_y += direction.at(1), counter++) {

    // If encountered an empty tile, there is no way for the move to sandwich the opponent color
    if (at(static_cast<std::size_t>(check_x), static_cast<std::size_t>(check_y)) == Empty) { return 0; }

    // If encountered an opponent color, there is still a chance to sandwich it
    if (at(static_cast<std::size_t>(check_x), static_cast<std::size_t>(check_y)) == !color) {
      exists_opposite = true;
      continue;
    }

    // If encountered the same color before the opposite color, then the piece cannot be placed
    if (!exists_opposite && (at(static_cast<std::size_t>(check_x), static_cast<std::size_t>(check_y)) == color)) {
      return 0;
    }

    // The opposing color is sandwiched by ours
    if (exists_opposite && (at(static_cast<std::size_t>(check_x), static_cast<std::size_t>(check_y)) == color)) {
      return counter;
    }
  }
  // Our color was not found in the given direction
  return 0;
}

int Board::place(std::size_t x, std::size_t y, Color color)
{
  bool place_success = false;

  // Check all directions
  const int DIRECTION_CNT = 8;
  const std::array<std::array<std::ptrdiff_t, 2>, DIRECTION_CNT> directions = { { { { 1, 0 } },
    { { 1, 1 } },
    { { 0, 1 } },
    { { -1, 1 } },
    { { -1, 0 } },
    { { -1, -1 } },
    { { 0, -1 } },
    { { 1, -1 } } } };
  for (std::array<std::ptrdiff_t, 2> direction : directions) {
    // Check if a specific direction can be changed
    int turn_count = checkDirection(x, y, direction, color);
    if (turn_count > 0) {
      place_success = true;

      // Turn the tiles, excluding the position we placed (we will turn this later)
      // if we edit the board now, then checkDirection would stop working for the next direction
      int counter = 0;
      for (std::ptrdiff_t turn_x = static_cast<std::ptrdiff_t>(x) + direction.at(0),
                          turn_y = static_cast<std::ptrdiff_t>(y) + direction.at(1);
           counter < turn_count;
           turn_x += direction.at(0), turn_y += direction.at(1), counter++) {
        edit(static_cast<std::size_t>(turn_x), static_cast<std::size_t>(turn_y), color);
      }
    }
  }
  if (place_success) {
    // Place the piece we previously did not place
    edit(x, y, color);
    history.emplace_back(board_state);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
