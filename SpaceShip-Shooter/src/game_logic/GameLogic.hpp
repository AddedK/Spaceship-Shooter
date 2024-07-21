#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include "Projectile.hpp"
#include "Ship.hpp"
#include "gameEnums.hpp"
#include <random>
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
constexpr int spawnEnemiesPerSecond = 4;

constexpr double enemyMoveSideProbability = 0.3;
constexpr int minFramesBetweenEnemyShipSideMove = 10;

constexpr int thresholdToSpawnBasicShip = 0;
constexpr int thresholdToSpawnAdvancedShip = 50;
constexpr int thresholdToSpawnStrikerShip = 80;
constexpr int thresholdToSpawnUltimateShip = 95;

}; // namespace GameConstants

class GameState {
  int frameNumber;
  int fps;
  int spawnEnemiesPerFrame;
  Ship player;
  std::vector<Ship> enemyShips;
  std::vector<Projectile> projectiles;
  int screenWidth;
  int screenHeight;
  bool playerIsAlive;

  std::mt19937 randomGenerator;

  void moveAllEnemies();
  void spawnEnemies();
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
      : frameNumber(0), fps(fps),
        spawnEnemiesPerFrame(fps * GameConstants::spawnEnemiesPerSecond),
        screenWidth(screenWidth), screenHeight(screenHeight),
        playerIsAlive(true) {

    std::random_device rd;              // obtain a random number from hardware
    std::mt19937 randomGenerator(rd()); // seed the generator
  }
  GameState(int fps, Ship player, int screenWidth, int screenHeight)
      : frameNumber(0), fps(fps), player(player), screenWidth(screenWidth),
        screenHeight(screenHeight), playerIsAlive(true) {

    std::random_device rd;
    std::mt19937 randomGenerator(rd());
  }
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

void moveShip(Ship &ship, MoveDirection direction, int screenWidth,
              int screenHeight, int additionalMovement = 0);
void moveProjectile(Projectile &projectile, int screenWidth, int screenHeight);

bool lineIsIntersecting(const Point &p1, const Point &q1, const Point &p2,
                        const Point &q2);

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
