#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include "Projectile.hpp"
#include "Ship.hpp"
#include "gameEnums.hpp"
#include <vector>
namespace GameLogic {

namespace GameConstants {
// Constants related to game logic
constexpr int playerWidth = 50;
constexpr int playerHeight = 50;
constexpr int playerInitialSpeed = 5;
constexpr int playerInitialNrOfLives = 3;
constexpr int playerInitialFramesBetweenShots = 30;

constexpr int enemyInitialSpeed = 1;
constexpr int enemyInitialNrOfLives = 1;

constexpr int projectileDefaultWidth = 3;
constexpr int projectileDefaultHeight = 3;
constexpr int projectileDefaultSpeed = 6;
}; // namespace GameConstants

class GameState {
  int frameNumber;
  int fps;
  Ship player;
  std::vector<Ship> enemyShips;
  std::vector<Projectile> projectiles;
  int screenWidth;
  int screenHeight;
  bool playerIsAlive;

  void moveAllEnemies();
  void clearEnemyShips();
  void movePlayer(MoveDirection direction);
  void addEnemyShip(
      Ship &&enemy); // TODO: sanity check on bounds on ship coordinations

  void addProjectile(Projectile &&projectile);
  void addPlayerProjectile();
  void removeAllProjectiles();
  void moveAllProjectiles();

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
  std::vector<Projectile> getProjectiles() const { return projectiles; }
  void playerLosesLife();
  void setPlayerAliveStatus(bool);
  bool getPlayerAliveStatus() const { return playerIsAlive; }

  void startGame();
  void updateGame();
  void playerAndShipCollisions();
  void shipAndProjectileCollisions();
  void checkAndHandleCollisions();

  // TODO: Make sanity checks on how people construct GameState
  GameState() = delete;
  GameState(int fps, int screenWidth, int screenHeight)
      : frameNumber(0), fps(fps), screenWidth(screenWidth),
        screenHeight(screenHeight), playerIsAlive(true) {}
  // Player default constructed
  GameState(int fps, Ship player, int screenWidth, int screenHeight)
      : frameNumber(0), fps(fps), player(player), screenWidth(screenWidth),
        screenHeight(screenHeight), playerIsAlive(true) {}
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

void moveShip(Ship &ship, MoveDirection direction, int screenWidth,
              int screenHeight);
void moveProjectile(Projectile &projectile, int screenWidth, int screenHeight);
} // namespace GameLogic

template <typename T, typename G> bool isColliding(const T &t, const G &g) {
  // Note that this fails if one object moves really fast, almost "teleporting"
  // through another object. This can sort of be mitigated by having high fps.
  // But I'll cross that bridge _IF_ I get to it

  bool yPositionOfTInG =
      (t.yPosition >= g.yPosition && (t.yPosition <= g.yPosition + g.height));

  bool yPositionOfGInT =
      !yPositionOfTInG &&
      (g.yPosition >= t.yPosition && (g.yPosition <= t.yPosition + t.height));

  bool xPositionOfTInG =
      (t.xPosition >= g.xPosition && (t.xPosition <= g.xPosition + g.width));

  bool xPositionOfGInT =
      !xPositionOfTInG &&
      (g.xPosition >= t.xPosition && (g.xPosition <= t.xPosition + t.width));

  return ((yPositionOfGInT || yPositionOfTInG) &&
          (xPositionOfTInG || xPositionOfGInT));
}

#endif // GAME_LOGIC_HPP
