#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include <vector>
namespace GameLogic {

#include "Ship.hpp"
enum class KeyPress { LEFT, UP, RIGHT, DOWN, ENTER, Q };

class GameState {
  Ship player;
  std::vector<Ship> enemyShips;
  int screenWidth;
  int screenHeight;

public:
  Ship getPlayer() const { return player; }
  void setPlayer(Ship player);
  void handleKeyPress(KeyPress keyPress);
  void movePlayer(KeyPress keyPress);
  void setDimensions(int screenWidth, int screenHeight);
  std::vector<Ship> getEnemyShips() const { return enemyShips; }
  void addEnemyShip(Ship &&enemy);

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
