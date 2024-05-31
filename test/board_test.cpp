#include "othello/board.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

TEST_CASE("Board is initialized", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.at(3, 3) == othello::Black);
  REQUIRE(test_board.at(3, 4) == othello::White);
  REQUIRE(test_board.at(4, 3) == othello::White);
  REQUIRE(test_board.at(4, 4) == othello::Black);
}

TEST_CASE("Attempting to place in invalid location should return faliure", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.place(0, 0, othello::White) == EXIT_FAILURE);
  REQUIRE(test_board.place(1, 5, othello::White) == EXIT_FAILURE);
  REQUIRE(test_board.place(6, 7, othello::White) == EXIT_FAILURE);
}

TEST_CASE("Attempting to access coordinates outside the board should throw", "[Board]")
{
  othello::Board test_board{};
  REQUIRE_THROWS_AS(test_board.at(20, 10), std::out_of_range);
  REQUIRE_THROWS_AS(test_board.at(40, 3), std::out_of_range);
  REQUIRE_THROWS_AS(test_board.at(0, 30), std::out_of_range);
  REQUIRE_THROWS_AS(test_board.at(50, 30), std::out_of_range);
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

TEST_CASE("Skipping and turn incrementation works", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.getTurn() == 1);
  REQUIRE_NOTHROW(test_board.noPlace());
  REQUIRE(test_board.getTurn() == 2);
  REQUIRE_NOTHROW(test_board.noPlace());
  REQUIRE(test_board.getTurn() == 3);
  REQUIRE_NOTHROW(test_board.noPlace());
  REQUIRE(test_board.getTurn() == 4);
  REQUIRE_NOTHROW(test_board.noPlace());
  REQUIRE(test_board.getTurn() == 5);
  REQUIRE_NOTHROW(test_board.noPlace());
  REQUIRE(test_board.getTurn() == 6);
  REQUIRE_NOTHROW(test_board.noPlace());
  REQUIRE(test_board.getTurn() == 7);
}

TEST_CASE("Reverting beyond the limit should return EXIT_FALIURE", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.revert() == EXIT_FAILURE);
  REQUIRE(test_board.revert(1) == EXIT_FAILURE);
  REQUIRE(test_board.revert(10) == EXIT_FAILURE);
}

TEST_CASE("Normal reverting tests", "[Board]")
{
  othello::Board test_board{};
  REQUIRE(test_board.place(2, 4, othello::Black) == EXIT_SUCCESS);
  REQUIRE(test_board.revert() == EXIT_SUCCESS);
  REQUIRE(test_board.at(3, 3) == othello::Black);
  REQUIRE(test_board.at(3, 4) == othello::White);
  REQUIRE(test_board.at(4, 3) == othello::White);
  REQUIRE(test_board.at(4, 4) == othello::Black);

  test_board.noPlace();
  test_board.noPlace();
  test_board.noPlace();
  REQUIRE(test_board.revert(3) == EXIT_SUCCESS);
}
