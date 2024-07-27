#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include "Projectile.hpp"
#include "Ship.hpp"
#include "Upgrade.hpp"
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

constexpr int projectileDefaultWidth = 5;
constexpr int projectileDefaultHeight = 5;
constexpr int projectileDefaultSpeed = 6;
constexpr int spawnEnemiesPerSecond = 4;

constexpr int upgradeDefaultRadius = 3;
constexpr int upgradeDefaultSpeed = 3;

constexpr double enemyMoveSideProbability = 0.3;
constexpr int minFramesBetweenEnemyShipSideMove = 10;

constexpr double spawnMovementSpeedUpgradeProbability = 0.02;
constexpr int movementSpeedUpgradeAmount = 2;
constexpr double spawnBonusLifeUpgradeProbability = 0.05;
constexpr double spawnProjectileSpeedUpgradeProbability = 0.04;
constexpr int projectileSpeedUpgradeAmount = 2;

constexpr int thresholdToSpawnBasicShip = 0;
constexpr int thresholdToSpawnAdvancedShip = 50;
constexpr int thresholdToSpawnStrikerShip = 80;
constexpr int thresholdToSpawnUltimateShip = 95;

constexpr int nrSecondsUntilBoostShipTypeThresholds = 60 * 1;
constexpr int shipTypeThresholdDifficultyBoost = 20;

constexpr int nrSecondsUntilBoostEnemyShipSwawnRate = 60 * 2;
constexpr int enemySwawnRateWaitReductionSeconds = 1;

}; // namespace GameConstants

class GameState {
  int frameNumber;
  int fps;
  int spawnEnemiesPerSecond;
  Ship player;
  std::vector<Ship> enemyShips;
  std::vector<Projectile> projectiles;
  std::vector<Upgrade> upgrades;
  int screenWidth;
  int screenHeight;
  bool playerIsAlive;

  std::mt19937 randomGenerator;

  int playerScore;
  int gameDifficulty;

  bool shouldBoostShipTypeThreshold;
  bool shouldBoostEnemyShipSpawnRate;

  int nrMovementSpeedUpgradesToSpawn;
  int nrBonusLifeUpgradesToSpawn;
  int nrProjectileSpeedUpgradesToSpawn;

  void moveAllEnemies();
  void spawnEnemies();
  void allEnemiesShoot();
  void clearEnemyShips();
  void movePlayer(MoveDirection direction);
  void addEnemyShip(Ship &&enemy);

  void addProjectile(Projectile &&projectile);
  void addPlayerProjectile();
  void removeAllProjectiles();
  void moveAllProjectiles();

  void addUpgrade(Upgrade &&upgrade);
  void spawnUpgrades();
  void removeAllUpgrades();
  void moveAllUpgrades();

  void playerLosesLife();
  void setPlayerAliveStatus(bool);

public:
  int getFrameNumber() const { return frameNumber; }
  Ship getPlayer() const { return player; }
  void setPlayer(Ship player);
  void setPlayerSpeed(int newSpeed); // Public for testing
  void handleKeyPress(KeyPress keyPress);
  int getScreenWidth() const { return screenWidth; }
  int getScreenHeight() const { return screenHeight; }
  std::vector<Ship> getEnemyShips() const {
    return enemyShips;
  } // Performance: Return by reference
  std::vector<Projectile> getProjectiles() const { return projectiles; }
  std::vector<Upgrade> getUpgrades() const { return upgrades; }
  bool getPlayerAliveStatus() const { return playerIsAlive; }
  int getPlayerScore() const { return playerScore; }
  int getGameDifficulty() const { return gameDifficulty; }

  void calculateDifficultyModifications();
  void startGame();
  void updateGame();
  void playerAndShipCollisions(); // Public for testing
  void playerAndUpgradeCollisions();
  void shipAndProjectileCollisions();
  void checkAndHandleCollisions();

  GameState() = delete;
  GameState(int fps, int screenWidth, int screenHeight)
      : frameNumber(0), fps(fps),
        spawnEnemiesPerSecond(GameConstants::spawnEnemiesPerSecond),
        screenWidth(screenWidth), screenHeight(screenHeight),
        playerIsAlive(true), playerScore(0), gameDifficulty(1),
        shouldBoostShipTypeThreshold(false),
        shouldBoostEnemyShipSpawnRate(false), nrMovementSpeedUpgradesToSpawn(1),
        nrBonusLifeUpgradesToSpawn(1), nrProjectileSpeedUpgradesToSpawn(1) {

    std::mt19937 randomGenerator(std::random_device{}()); // seed the generator
  }
  GameState(int fps, Ship player, int screenWidth, int screenHeight)
      : frameNumber(0), fps(fps),
        spawnEnemiesPerSecond(GameConstants::spawnEnemiesPerSecond),
        player(player), screenWidth(screenWidth), screenHeight(screenHeight),
        playerIsAlive(true), playerScore(0), gameDifficulty(1),
        shouldBoostShipTypeThreshold(false),
        shouldBoostEnemyShipSpawnRate(false), nrMovementSpeedUpgradesToSpawn(1),
        nrBonusLifeUpgradesToSpawn(1), nrProjectileSpeedUpgradesToSpawn(1) {

    std::mt19937 randomGenerator(std::random_device{}());
  }
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

void moveShip(Ship &ship, MoveDirection direction, int screenWidth,
              int screenHeight, int additionalMovement = 0);
void moveProjectile(Projectile &projectile, int screenWidth, int screenHeight);
void moveUpgrade(Upgrade &upgrade, int screenWidth, int screenHeight);

int sq(int x);
double distance(Point p1, Point p2);
bool lineLineIntersection(const Point &p1, const Point &q1, const Point &p2,
                          const Point &q2);

int orientation(const Point &p, const Point &q, const Point &r);
bool lineCircleIntersection(Point p1, Point p2, Point c1, int radius);

bool onSegment(const Point &p, const Point &q, const Point &r);

template <typename T, typename G>
bool isCollidingPolygonPolygon(const T &t, const G &g) {
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
      if (lineLineIntersection(t1, t2, g1, g2)) {
        return true;
      }
    }
  }
  return false;
}

template <typename T, typename G>
bool isCollidingPolygonCircle(const T &p, const G &c) {
  for (int i = 0; i < p.vertices.size(); i++) {
    int j = (i + 1) % p.vertices.size();
    Point p1 = p.vertices[i];
    Point p2 = p.vertices[j];

    if (lineCircleIntersection(p1, p2, c.center, c.radius)) {
      return true;
    }
  }
  return false;
}
} // namespace GameLogic

#endif // GAME_LOGIC_HPP
