#include "othello/board.hpp"
#include <catch2/catch_test_macros.hpp>

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
