#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include <vector>
namespace GameLogic {

#include "Ship.hpp"
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

public:
  Ship getPlayer() const { return player; }
  void setPlayer(Ship player);
  void handleKeyPress(KeyPress keyPress);
  void movePlayer(MoveDirection direction);
  void setDimensions(int screenWidth, int screenHeight);
  std::vector<Ship> getEnemyShips() const { return enemyShips; }
  void addEnemyShip(Ship &&enemy);
  void clearEnemyShips();

  void moveShip(Ship &ship, MoveDirection direction);
  void update();
  void moveAllEnemies();

  void startGame();
  // TODO: Make sanity checks on how people construct GameState
  GameState() = delete;
  GameState(int screenWidth, int screenHeight)
      : screenWidth(screenWidth), screenHeight(screenHeight) {}
  // Ship default constructed
  GameState(Ship player, int screenWidth, int screenHeight)
      : player(player), screenWidth(screenWidth), screenHeight(screenHeight) {}
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

} // namespace GameLogic

#endif // GAME_LOGIC_HPP
