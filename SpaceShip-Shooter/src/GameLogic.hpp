#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include "Ship.hpp"
#include <vector>
namespace GameLogic {

enum class KeyPress { LEFT, UP, RIGHT, DOWN, ENTER, Q };
enum class MoveDirection { LEFT, UP, RIGHT, DOWN };

namespace GameConstants {
// Constants related to game logic
constexpr int playerWidth = 50;
constexpr int playerHeight = 50;
}; // namespace GameConstants

class GameState {
  Ship player;
  std::vector<Ship> enemyShips;
  int screenWidth;
  int screenHeight;
  void moveAllEnemies();
  void clearEnemyShips();
  void movePlayer(MoveDirection direction);
  void addEnemyShip(
      Ship &&enemy); // TODO: sanity check on bounds on ship coordinations

public:
  Ship getPlayer() const { return player; }
  void
  setPlayer(Ship player); // TODO: Sanity check on bounds on player coordinates
  void setPlayerSpeed(int newSpeed);
  void handleKeyPress(KeyPress keyPress);
  int getScreenWidth() const { return screenWidth; }
  int getScreenHeight() const { return screenHeight; }
  std::vector<Ship> getEnemyShips() const {
    return enemyShips;
  } // Performance: Return by reference

  void update();

  void startGame();
  // TODO: Make sanity checks on how people construct GameState
  GameState() = delete;
  GameState(int screenWidth, int screenHeight)
      : screenWidth(screenWidth), screenHeight(screenHeight) {}
  // Player default constructed
  GameState(Ship player, int screenWidth, int screenHeight)
      : player(player), screenWidth(screenWidth), screenHeight(screenHeight) {}
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

void moveShip(Ship &ship, MoveDirection direction, int screenWidth,
              int screenHeight);
} // namespace GameLogic

#endif // GAME_LOGIC_HPP
