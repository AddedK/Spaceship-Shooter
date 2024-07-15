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
constexpr int enemyInitialFramesBetweenShots = 60;

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
  void allEnemiesShoot();
  void clearEnemyShips();
  void movePlayer(MoveDirection direction);
  void addEnemyShip(
      Ship &&enemy); // TODO: sanity check on bounds on ship coordinations

  void addProjectile(Projectile &&projectile);
  void addPlayerProjectile();
  void removeAllProjectiles();
  void moveAllProjectiles();

  void playerLosesLife();
  void setPlayerAliveStatus(bool);

public:
  Ship getPlayer() const { return player; }
  void
  setPlayer(Ship player); // TODO: Sanity check on bounds on player coordinates
  void setPlayerSpeed(int newSpeed); // Public for testing
  void handleKeyPress(KeyPress keyPress);
  int getScreenWidth() const { return screenWidth; }
  int getScreenHeight() const { return screenHeight; }
  std::vector<Ship> getEnemyShips() const {
    return enemyShips;
  } // Performance: Return by reference
  std::vector<Projectile> getProjectiles() const { return projectiles; }
  bool getPlayerAliveStatus() const { return playerIsAlive; }

  void startGame();
  void updateGame();
  void playerAndShipCollisions(); // Public for testing
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

bool lineIsIntersecting(const Point &t1, const Point &t2, const Point &g1,
                        const Point &g2);

int orientation(const Point &p, const Point &q, const Point &r);

bool onSegment(const Point &p, const Point &q, const Point &r);

template <typename T, typename G>
bool isCollidingBetter(const T &t, const G &g) {
  for (int i = 0; i < t.vertices.size(); i++) {
    int j = (i + 1) % t.vertices.size();
    Point t1 = t.vertices[i];
    Point t2 = t.vertices[j];

    // Now we have pair of vertices from t
    for (int k = 0; k < g.vertices.size(); k++) {
      int l = (k + 1) % g.vertices.size();
      // now we have pair of vertices from g
      Point g1 = g.vertices[k];
      Point g2 = g.vertices[l];
      if (lineIsIntersecting(t1, t2, g1, g2)) {
        return true;
      }
    }
  }
  return false;
}
} // namespace GameLogic

#endif // GAME_LOGIC_HPP
