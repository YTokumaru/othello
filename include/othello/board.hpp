#ifndef OTHELLO_HPP
#define OTHELLO_HPP
#include <array>
#include <cstddef>
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
   * @brief Edit the board at the coordinate (x,y)
   * @param x The x coordinate
   * @param y The y coordinate
   * @param color The color to place
   * @return EXIT_SUCCESS
   */
  int edit(std::size_t x, std::size_t y, othello::Color color);


  /**
   * @brief Changes the board by a piece on (x,y)
   * @param x The x coordinate on the board
   * @param y The y coordinate on the board
   * @return EXIT_SUCCESS if successfully placed and board changed, otherwise EXIT_FAILURE
   */
  int place(std::size_t x, std::size_t y, othello::Color color);

  /**
   * @brief Increment the turn without placing any piece
   */
  void noPlace();

  /**
   * @brief Returns the color at the given coordinate
   * @param x The x coordinate
   * @param t The y coordinate
   * @return The color of the board
   */
  [[nodiscard]] othello::Color at(std::size_t x, std::size_t y) const;
  othello::Color &at(std::size_t x, std::size_t y);

  /**
   * @brief Checks whether the color is placable on the current board
   * @return True if placable, false if not
   */
  [[nodiscard]] bool isPlacable(othello::Color color) const;

  /**
   * @brief Checks whether the color is placable on the given coordinate
   * @param x The x coordinate
   * @param y The y coordinate
   * @return True if placable, otherwise false
   */
  [[nodiscard]] bool isPlacable(std::size_t x, std::size_t y, othello::Color color) const;


  /**
   * @brief Revert board to a previous state
   * @return EXIT_SUCCESS if reverted, else false
   */
  int revert();

  /**
   * @brief Revert board to a previous state
   * @param count The numeber of times to revert
   * @return EXIT_SUCCESS if reverted, else false
   */
  int revert(std::size_t count);

  /**
   * @brief Return the number of the turns made
   * @return The numbers of turns made
   */
  [[nodiscard]] size_t getTurn() const;

  /**
   * @brief Get the color of the player to play the next move
   * @return Color of the next player
   */
  [[nodiscard]] inline othello::Color getNextColor() const noexcept
  {
    return getTurn() % 2 == 0 ? othello::White : othello::Black;
  };

private:
  /**
   * @brief Returns the number of tiles that can be changed in the given direction
   * @param x The x coordinate to place
   * @param y The y coordinate to place
   * @param direction The direction to check, as (x,y) vector eg. (1,-1)
   * @param color The color to place
   * @return The number of tiles that can be changed into the given direction, excluding the placing piece
   */
  [[nodiscard]] int
    checkDirection(std::size_t x, std::size_t y, std::array<std::ptrdiff_t, 2> direction, othello::Color color) const;

  std::array<std::array<othello::Color, BOARD_WIDTH>, BOARD_HEIGHT>
    board_state = {}; /**< The current state of the board */

  std::vector<std::array<std::array<othello::Color, BOARD_WIDTH>, BOARD_HEIGHT>>
    history; /**< The history of the board */
};

}// namespace othello
#endif// !OTHELLO_HPP
