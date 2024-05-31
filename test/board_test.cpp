#include "othello/board.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>

TEST_CASE("Board is initialized", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.at(3, 3) == othello::Black);
  REQUIRE(test_board.at(3, 4) == othello::White);
  REQUIRE(test_board.at(4, 3) == othello::White);
  REQUIRE(test_board.at(4, 4) == othello::Black);
}

TEST_CASE("First few moves are possible", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.place(2, 4, othello::Black) == EXIT_SUCCESS);
  REQUIRE(test_board.at(2, 4) == othello::Black);
  REQUIRE(test_board.at(3, 4) == othello::Black);
  REQUIRE(test_board.at(4, 4) == othello::Black);
  REQUIRE(test_board.at(3, 3) == othello::Black);
  REQUIRE(test_board.at(4, 3) == othello::White);
}

TEST_CASE("Initial board should be placable", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.isPlacable(othello::White) == true);
  REQUIRE(test_board.isPlacable(othello::Black) == true);
}

TEST_CASE("Filled board should not be placable", "[Board]")
{
  othello::Board test_board{};

  // Fill the board
  for (std::size_t x = 0; x < othello::BOARD_WIDTH; x++) {
    for (std::size_t y = 0; y < othello::BOARD_HEIGHT; y++) { test_board.edit(x, y, othello::Black); }
  }

  REQUIRE(test_board.isPlacable(othello::Black) == false);
  REQUIRE(test_board.isPlacable(othello::White) == false);

  // Fill the board with white
  for (std::size_t x = 0; x < othello::BOARD_WIDTH; x++) {
    for (std::size_t y = 0; y < othello::BOARD_HEIGHT; y++) { test_board.edit(x, y, othello::White); }
  }

  REQUIRE(test_board.isPlacable(othello::Black) == false);
  REQUIRE(test_board.isPlacable(othello::White) == false);
}
