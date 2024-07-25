#include "GameLogic.hpp"
#include "Ship.hpp"
#include "Upgrade.hpp"
#include "gameEnums.hpp"
#include <iostream>
#include <map>
#include <random>

namespace GameLogic {

std::map<KeyPress, MoveDirection> keyToDirection = {
    {KeyPress::UP, MoveDirection::UP},
    {KeyPress::DOWN, MoveDirection::DOWN},
    {KeyPress::LEFT, MoveDirection::LEFT},
    {KeyPress::RIGHT, MoveDirection::RIGHT}};

std::map<ShipType, int> scorePerDestroyedShip = {{ShipType::BASIC, 10},
                                                 {ShipType::ADVANCED, 20},
                                                 {ShipType::STRIKER, 20},
                                                 {ShipType::ULTIMATE, 35}

};

void GameState::handleKeyPress(KeyPress keyPress) {
  switch (keyPress) {
  case KeyPress::UP:
  case KeyPress::DOWN:
  case KeyPress::LEFT:
  case KeyPress::RIGHT:
    movePlayer(keyToDirection[keyPress]);
    break;
  case KeyPress::SPACE:
    addPlayerProjectile();
    break;
  default:
    // TODO
    break;
  }
}

void GameState::movePlayer(MoveDirection direction) {
  // TODO: Allow special behavior for moving player
  moveShip(player, direction, screenWidth, screenHeight);
}

void GameState::setPlayer(Ship player) { this->player = player; }
void GameState::setPlayerSpeed(int newSpeed) {
  player.setMovementSpeed(newSpeed);
}
void GameState::addEnemyShip(Ship &&enemy) {
  this->enemyShips.push_back(enemy);
}
void GameState::clearEnemyShips() { this->enemyShips.clear(); }
void moveShip(Ship &ship, MoveDirection direction, int screenWidth,
              int screenHeight, int additionalMovement) {
  int totalMovement = ship.movementSpeed + additionalMovement;

  std::vector<Point> &vertices = ship.vertices;
  switch (direction) {
  case MoveDirection::UP: {
    int clippedMovement =
        (ship.lowestY - totalMovement) < 0 ? ship.lowestY : totalMovement;
    for (auto &point : vertices) {
      point.y -= clippedMovement;
    }
    ship.lowestY -= clippedMovement;
    ship.highestY -= clippedMovement;
    break;
  }
  case MoveDirection::DOWN: {
    int clippedMovement = (ship.highestY + totalMovement) > screenHeight
                              ? screenHeight - ship.highestY
                              : totalMovement;
    for (auto &point : vertices) {
      point.y += clippedMovement;
    }
    ship.lowestY += clippedMovement;
    ship.highestY += clippedMovement;
    break;
  }
  case MoveDirection::LEFT: {
    int clippedMovement =
        (ship.lowestX - totalMovement) < 0 ? ship.lowestX : totalMovement;

    for (auto &point : vertices) {
      point.x -= clippedMovement;
    }
    ship.lowestX -= clippedMovement;
    ship.highestX -= clippedMovement;
    ship.middlePositionX -= clippedMovement;
    break;
  }
  case MoveDirection::RIGHT: {
    int clippedMovement = (ship.highestX + totalMovement) > screenWidth
                              ? screenWidth - ship.highestX
                              : totalMovement;
    for (auto &point : vertices) {
      point.x += clippedMovement;
    }
    ship.lowestX += clippedMovement;
    ship.highestX += clippedMovement;
    ship.middlePositionX += clippedMovement;
    break;
  }
  default:
    // TODO
    break;
  }
}

void GameState::allEnemiesShoot() {
  // TODO Diffierent ships with different firing mechanics
  for (auto &enemyShip : enemyShips) {
    if (enemyShip.highestY < screenHeight &&
        ((frameNumber - enemyShip.frameWhenLastFiredProjectile) >=
         GameConstants::enemyInitialFramesBetweenShots)) {
      int xPositionMiddle = enemyShip.middlePositionX;
      std::vector<Point> projectilePoints;
      projectilePoints.push_back(
          {xPositionMiddle - GameConstants::projectileDefaultWidth / 2,
           enemyShip.highestY + 1});
      projectilePoints.push_back(
          {xPositionMiddle - GameConstants::projectileDefaultWidth / 2,
           enemyShip.highestY + 1 + GameConstants::projectileDefaultHeight});
      projectilePoints.push_back(
          {xPositionMiddle + GameConstants::projectileDefaultWidth / 2,
           enemyShip.highestY + 1 + GameConstants::projectileDefaultHeight});
      projectilePoints.push_back(
          {xPositionMiddle + GameConstants::projectileDefaultWidth / 2,
           enemyShip.highestY + 1});
      Projectile projectile(projectilePoints, enemyShip.projectileSpeed,
                            MoveDirection::DOWN);
      if (enemyShip.shipType == ShipType::STRIKER ||
          enemyShip.shipType == ShipType::ULTIMATE) {
        projectile.isHoming = true;
      }

      addProjectile(std::move(projectile));
      enemyShip.frameWhenLastFiredProjectile = frameNumber;
    }
  }
  return;
}

void GameState::spawnEnemies() {
  int spawnEnemyFaster = shouldBoostEnemyShipSpawnRate
                             ? GameConstants::enemySwawnRateWaitReductionSeconds
                             : 0;
  if ((frameNumber % fps == 0) &&
      (frameNumber / fps) % (spawnEnemiesPerSecond - spawnEnemyFaster) == 0 &&
      frameNumber != 0) {
    int lowXBound = 0 + GameConstants::playerWidth;
    int highXBound = screenWidth - GameConstants::playerWidth;
    std::uniform_int_distribution<> distr(lowXBound,
                                          highXBound); // define the range
    int centerX = distr(randomGenerator);
    std::vector<Point> enemyVertices;
    enemyVertices.push_back(Point{centerX - GameConstants::playerWidth / 2, 0});
    enemyVertices.push_back(Point{centerX, GameConstants::playerHeight});
    enemyVertices.push_back(Point{centerX + GameConstants::playerWidth / 2, 0});
    Ship enemyShip(enemyVertices, GameConstants::enemyInitialSpeed,
                   GameConstants::enemyInitialNrOfLives,
                   GameConstants::projectileDefaultSpeed);

    std::uniform_real_distribution<> distr2(0, 1);
    enemyShip.probabilityOfSideMoveRight = distr2(randomGenerator);

    std::uniform_int_distribution<> distrShipType(0, 100);
    int shipTypeThreshold = distrShipType(randomGenerator);
    if (shouldBoostShipTypeThreshold) {
      shipTypeThreshold += GameConstants::shipTypeThresholdDifficultyBoost;
    }
    if (shipTypeThreshold >= GameConstants::thresholdToSpawnUltimateShip) {
      enemyShip.shipType = ShipType::ULTIMATE;
      enemyShip.addNrOfLives(2);
    } else if (shipTypeThreshold >=
               GameConstants::thresholdToSpawnStrikerShip) {
      enemyShip.shipType = ShipType::STRIKER;
      enemyShip.setMovementSpeed(enemyShip.movementSpeed + 4);
    } else if (shipTypeThreshold >=
               GameConstants::thresholdToSpawnAdvancedShip) {
      enemyShip.addNrOfLives(1);
      enemyShip.shipType = ShipType::ADVANCED;
    } else {
      enemyShip.shipType = ShipType::BASIC;
    }
    addEnemyShip(std::move(enemyShip));
  }
}

void GameState::calculateDifficultyModifications() {
  if (!shouldBoostShipTypeThreshold &&
      (frameNumber / fps >=
       GameConstants::nrsecondsUntilBoostShipTypeThresholds)) {
    shouldBoostShipTypeThreshold = true;
  }
  if (!shouldBoostEnemyShipSpawnRate &&
      (frameNumber / fps) >=
          GameConstants::nrsecondsUntilBoostEnemyShipSwawnRate) {
    shouldBoostEnemyShipSpawnRate = true;
  }
  gameDifficulty = 1;
  if (shouldBoostShipTypeThreshold) {
    gameDifficulty += 1;
  }
  if (shouldBoostEnemyShipSpawnRate) {
    gameDifficulty += 1;
  }
}
void GameState::updateGame() {
  ++frameNumber;
  calculateDifficultyModifications();
  if (frameNumber % fps == 0) {
    playerScore++;
  }
  if (getPlayerAliveStatus()) {
    moveAllEnemies();
    spawnEnemies();
    moveAllProjectiles();
    allEnemiesShoot();
    spawnUpgrades();
    moveAllUpgrades();
    checkAndHandleCollisions();
  } else {
    std::cout << "Player is dead!" << std::endl;
  }
}
void GameState::moveAllEnemies() {
  for (auto shipIterator = enemyShips.begin();
       shipIterator != enemyShips.end();) {
    auto &enemyShip = *shipIterator;
    if (enemyShip.highestY == screenHeight) {
      shipIterator = enemyShips.erase(shipIterator);
      continue;
    }

    moveShip(enemyShip, MoveDirection::DOWN, screenWidth, screenHeight);

    // Small probability to move left or right
    std::uniform_real_distribution<> distr(0, 1);
    bool shouldSideMove =
        distr(randomGenerator) >= GameConstants::enemyMoveSideProbability &&
        frameNumber - enemyShip.frameWhenLastMovedSide >=
            GameConstants::minFramesBetweenEnemyShipSideMove;

    if (shouldSideMove) {
      bool shouldGoRight =
          distr(randomGenerator) <= enemyShip.probabilityOfSideMoveRight;
      MoveDirection sideDirection =
          shouldGoRight ? MoveDirection::RIGHT : MoveDirection::LEFT;
      moveShip(enemyShip, sideDirection, screenWidth, screenHeight, 16);
      enemyShip.frameWhenLastMovedSide = frameNumber;
    }
    ++shipIterator;
  }
}

void GameState::startGame() {
  setPlayerAliveStatus(true);
  frameNumber = 0;
  playerScore = 0;
  nrMovementSpeedUpgradesToSpawn = 1;
  nrBonusLifeUpgradesToSpawn = 1;
  nrProjectileSpeedUpgradesToSpawn = 1;

  std::vector<Point> playerVertices;
  playerVertices.push_back(
      Point{screenWidth / 2, screenHeight - GameConstants::playerHeight});
  playerVertices.push_back(
      Point{screenWidth / 2 - GameConstants::playerWidth / 2, screenHeight});
  playerVertices.push_back(
      Point{screenWidth / 2 + GameConstants::playerWidth / 2, screenHeight});
  setPlayer({playerVertices, GameConstants::playerInitialSpeed,
             GameConstants::playerInitialNrOfLives,
             GameConstants::projectileDefaultSpeed});
  clearEnemyShips();
  removeAllProjectiles();
  removeAllUpgrades();
  std::vector<Point> enemyVertices;
  enemyVertices.push_back(
      Point{screenWidth / 2 - GameConstants::playerWidth / 2, 0});
  enemyVertices.push_back(Point{screenWidth / 2, GameConstants::playerWidth});
  enemyVertices.push_back(
      Point{screenWidth / 2 + GameConstants::playerWidth / 2, 0});
  Ship enemyShip(enemyVertices, GameConstants::enemyInitialSpeed,
                 GameConstants::enemyInitialNrOfLives,
                 GameConstants::projectileDefaultSpeed);
  addEnemyShip(std::move(enemyShip));
}

void GameState::addProjectile(Projectile &&projectile) {
  this->projectiles.push_back(projectile);
}
void GameState::addPlayerProjectile() {
  if (player.lowestY > 0 &&
          ((frameNumber - player.frameWhenLastFiredProjectile) >=
           GameConstants::playerInitialFramesBetweenShots) ||
      frameNumber == 0) {
    int xPositionMiddle = player.middlePositionX;
    std::vector<Point> projectilePoints;
    projectilePoints.push_back(
        {xPositionMiddle - GameConstants::projectileDefaultWidth / 2,
         player.lowestY - 1});
    projectilePoints.push_back(
        {xPositionMiddle + GameConstants::projectileDefaultWidth / 2,
         player.lowestY - 1});
    projectilePoints.push_back(
        {xPositionMiddle + GameConstants::projectileDefaultWidth / 2,
         player.lowestY - 1 - GameConstants::projectileDefaultHeight});
    projectilePoints.push_back(
        {xPositionMiddle - GameConstants::projectileDefaultWidth / 2,
         player.lowestY - 1 - GameConstants::projectileDefaultHeight});
    Projectile projectile(projectilePoints, player.projectileSpeed,
                          MoveDirection::UP);

    addProjectile(std::move(projectile));
    player.frameWhenLastFiredProjectile = frameNumber;
  }
}

void GameState::moveAllProjectiles() {
  // Remove all projectiles that are at the bottom or top
  for (auto begin = projectiles.begin(); begin != projectiles.end();) {
    if (begin->lowestY == 0 || begin->highestY == screenHeight) {
      begin = projectiles.erase(begin);
    } else {
      moveProjectile(*begin, screenWidth, screenHeight);
      if (begin->isHoming) {
        MoveDirection oldDirection = begin->direction;
        int oldSpeed = begin->movementSpeed;

        MoveDirection sideHoming =
            (begin->middlePositionX < player.middlePositionX)
                ? MoveDirection::RIGHT
                : MoveDirection::LEFT;

        begin->direction = sideHoming;
        begin->setMovementSpeed(2);
        moveProjectile(*begin, screenWidth, screenHeight);
        begin->direction = oldDirection;
        begin->setMovementSpeed(oldSpeed);
      }
      ++begin;
    }
  }
}

void moveProjectile(Projectile &projectile, int screenWidth, int screenHeight) {
  // Code duplication but it's okay
  std::vector<Point> &projectileVertices = projectile.vertices;
  switch (projectile.direction) {
  case MoveDirection::UP: {
    int clippedMovement = (projectile.lowestY - projectile.movementSpeed < 0)
                              ? projectile.lowestY
                              : projectile.movementSpeed;
    for (auto &point : projectileVertices) {
      point.y -= clippedMovement;
    }
    projectile.lowestY -= clippedMovement;
    projectile.highestY -= clippedMovement;
    break;
  }
  case MoveDirection::DOWN: {
    int clippedMovement =
        (projectile.highestY + projectile.movementSpeed > screenHeight)
            ? screenHeight - projectile.highestY
            : projectile.movementSpeed;
    for (auto &point : projectileVertices) {
      point.y += clippedMovement;
    }
    projectile.lowestY += clippedMovement;
    projectile.highestY += clippedMovement;

    break;
  }
  case MoveDirection::LEFT: {
    int clippedMovement = (projectile.lowestX - projectile.movementSpeed < 0)
                              ? projectile.lowestX
                              : projectile.movementSpeed;
    for (auto &point : projectileVertices) {
      point.x -= clippedMovement;
    }
    projectile.lowestX -= clippedMovement;
    projectile.highestX -= clippedMovement;
    projectile.middlePositionX -= clippedMovement;

    break;
  }
  case MoveDirection::RIGHT: {
    int clippedMovement =
        (projectile.highestX + projectile.movementSpeed > screenWidth)
            ? screenHeight - projectile.highestX
            : projectile.movementSpeed;
    for (auto &point : projectileVertices) {
      point.x += clippedMovement;
    }
    projectile.lowestX += clippedMovement;
    projectile.highestX += clippedMovement;
    projectile.middlePositionX += clippedMovement;

    break;
  }
  default:
    // TODO
    break;
  }
}
void GameState::removeAllProjectiles() { this->projectiles.clear(); }

void GameState::spawnUpgrades() {
  if (frameNumber % fps == 0) {

    bool canSpawnMovementSpeedUpgrade = nrMovementSpeedUpgradesToSpawn > 0;
    bool canSpawnBonusLifeUpgrade = nrBonusLifeUpgradesToSpawn > 0;
    bool canSpawnProjectileSpeedUpgrade = nrProjectileSpeedUpgradesToSpawn > 0;
    for (auto upgrade : upgrades) {
      if (upgrade.upgradeType == UpgradeType::MOVEMENTSPEED) {
        canSpawnMovementSpeedUpgrade = false;
      } else if (upgrade.upgradeType == UpgradeType::BONUSLIFE) {
        canSpawnBonusLifeUpgrade = false;
      } else if (upgrade.upgradeType == UpgradeType::PROJECTILESPEED) {
        canSpawnProjectileSpeedUpgrade = false;
      }
    }
    std::uniform_real_distribution<> distr(0, 1);
    double rollForMovementSpeed = distr(randomGenerator);
    double rollForBonusLife = distr(randomGenerator);
    double rollForProjectileSpeed = distr(randomGenerator);

    if (canSpawnMovementSpeedUpgrade &&
        rollForMovementSpeed >=
            GameConstants::spawnMovementSpeedUpgradeProbability) {
      Upgrade upgrade({screenWidth / 5, 0}, GameConstants::upgradeDefaultRadius,
                      GameConstants::upgradeDefaultSpeed, MoveDirection::DOWN,
                      UpgradeType::MOVEMENTSPEED);
      addUpgrade(std::move(upgrade));
    }

    if (canSpawnBonusLifeUpgrade &&
        rollForBonusLife >= GameConstants::spawnBonusLifeUpgradeProbability) {
      Upgrade upgrade({2 * screenWidth / 5, 0},
                      GameConstants::upgradeDefaultRadius,
                      GameConstants::upgradeDefaultSpeed, MoveDirection::DOWN,
                      UpgradeType::BONUSLIFE);
      addUpgrade(std::move(upgrade));
    }

    if (canSpawnProjectileSpeedUpgrade &&
        rollForBonusLife >=
            GameConstants::spawnProjectileSpeedUpgradeProbability) {
      Upgrade upgrade({4 * screenWidth / 5, 0},
                      GameConstants::upgradeDefaultRadius,
                      GameConstants::upgradeDefaultSpeed, MoveDirection::DOWN,
                      UpgradeType::PROJECTILESPEED);
      addUpgrade(std::move(upgrade));
    }
  }
}

void GameState::addUpgrade(Upgrade &&upgrade) {
  this->upgrades.push_back(upgrade);
}
void GameState::moveAllUpgrades() {
  // Remove all upgrades that are at the bottom
  for (auto begin = upgrades.begin(); begin != upgrades.end();) {
    if (begin->center.y == screenHeight) {
      begin = upgrades.erase(begin);
    } else {
      moveUpgrade(*begin, screenWidth, screenHeight);
      ++begin;
    }
  }
}

void moveUpgrade(Upgrade &upgrade, int screenWidth, int screenHeight) {
  switch (upgrade.direction) {
  case MoveDirection::UP: {
    int clippedMovement = (upgrade.center.y - upgrade.movementSpeed < 0)
                              ? upgrade.center.y
                              : upgrade.movementSpeed;
    upgrade.center.y -= clippedMovement;
    break;
  }
  case MoveDirection::DOWN: {
    int clippedMovement =
        (upgrade.center.y + upgrade.movementSpeed > screenHeight)
            ? screenHeight - upgrade.center.y
            : upgrade.movementSpeed;
    upgrade.center.y += clippedMovement;

    break;
  }
  case MoveDirection::LEFT: {
    int clippedMovement = (upgrade.center.x - upgrade.movementSpeed < 0)
                              ? upgrade.center.x
                              : upgrade.movementSpeed;
    upgrade.center.x -= clippedMovement;

    break;
  }
  case MoveDirection::RIGHT: {
    int clippedMovement =
        (upgrade.center.x + upgrade.movementSpeed > screenWidth)
            ? screenHeight - upgrade.center.x
            : upgrade.movementSpeed;
    upgrade.center.x += clippedMovement;

    break;
  }
  default:
    // TODO
    break;
  }
}
void GameState::removeAllUpgrades() { this->upgrades.clear(); }

void GameState::setPlayerAliveStatus(bool status) {
  this->playerIsAlive = status;
}

void GameState::playerLosesLife() {
  player.decrementNrOfLives(1);
  if (player.getNrOfLives() <= 0) {
    std::cout << "Player lost a life and died" << std::endl;
    std::cout << "Player final score: " << playerScore << std::endl;
    setPlayerAliveStatus(false);
  }
}

void GameState::playerAndUpgradeCollisions() {
  if (!getPlayerAliveStatus()) {
    return;
  }
  for (auto begin = upgrades.begin(); begin != upgrades.end();) {
    if (isCollidingPolygonCircle(player, *begin)) {
      switch (begin->upgradeType) {
      case GameLogic::UpgradeType::MOVEMENTSPEED: {
        player.setMovementSpeed(player.movementSpeed +
                                GameConstants::movementSpeedUpgradeAmount);
        nrMovementSpeedUpgradesToSpawn -= 1;
        break;
      }
      case GameLogic::UpgradeType::BONUSLIFE: {
        player.addNrOfLives(1);
        nrBonusLifeUpgradesToSpawn -= 1;
        break;
      }
      case GameLogic::UpgradeType::PROJECTILESPEED: {
        player.projectileSpeed += GameConstants::projectileSpeedUpgradeAmount;
        nrProjectileSpeedUpgradesToSpawn -= 1;
        break;
      }
      }
      begin = upgrades.erase(begin);
    } else {
      ++begin;
    }
  }
}

void GameState::playerAndShipCollisions() {
  if (!getPlayerAliveStatus()) {
    return;
  }
  for (auto begin = enemyShips.begin(); begin != enemyShips.end();) {
    if (isCollidingPolygonPolygon(player, *begin)) {
      playerLosesLife();
      begin->decrementNrOfLives(1);
      if (begin->getNrOfLives() == 0) {
        playerScore += scorePerDestroyedShip[begin->shipType];
        begin = enemyShips.erase(begin);
      } else {
        ++begin;
      }
      if (!getPlayerAliveStatus()) {
        return;
      }
    } else {
      ++begin;
    }
  }
}

void GameState::shipAndProjectileCollisions() {
  if (!getPlayerAliveStatus()) {
    return;
  }
  for (auto projectileIterator = projectiles.begin();
       projectileIterator != projectiles.end();) {

    // Check player collision
    if (getPlayerAliveStatus() &&
        isCollidingPolygonPolygon(player, *projectileIterator)) {
      playerLosesLife();
      projectileIterator = projectiles.erase(projectileIterator);
    } else {
      // Check if projectile hits another ship
      if (projectileIterator->direction == MoveDirection::DOWN) {
        ++projectileIterator;
        continue;
      }
      bool shouldAdvanceProjectileIterator = true;
      for (auto shipIterator = enemyShips.begin();
           shipIterator != enemyShips.end();) {
        if (isCollidingPolygonPolygon(*shipIterator, *projectileIterator)) {
          shipIterator->decrementNrOfLives(1);
          if (shipIterator->getNrOfLives() == 0) {
            playerScore += scorePerDestroyedShip[shipIterator->shipType];
            shipIterator = enemyShips.erase(shipIterator);
          } else {
            ++shipIterator;
          }
          projectileIterator = projectiles.erase(projectileIterator);
          shouldAdvanceProjectileIterator = false;
          break;
        } else {
          ++shipIterator;
        }
      }
      if (shouldAdvanceProjectileIterator) {
        ++projectileIterator;
      }
    }
  }
  return;
}

void GameState::checkAndHandleCollisions() {
  // Opinion: If two ships and a projectile are in the same spot and the ships
  // can destory each other, then only projectile goes unscathed
  playerAndUpgradeCollisions();
  playerAndShipCollisions();
  if (getPlayerAliveStatus()) {
    shipAndProjectileCollisions();
  }
}

int sq(int x) { return x * x; }

double distance(Point p1, Point p2) {
  return std::sqrt(sq(p2.x - p1.x) + sq(p2.y - p1.y));
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 -> p, q and r are collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(const Point &p, const Point &q, const Point &r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (val == 0)
    return 0;               // collinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(const Point &p, const Point &q, const Point &r) {
  if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
      q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
    return true;

  return false;
}

// The main function that returns true if the line segment 'p1q1' and 'p2q2'
// intersect.
bool lineLineIntersection(const Point &p1, const Point &q1, const Point &p2,
                          const Point &q2) {
  // Find the four orientations needed for general and special cases
  int o1 = orientation(p1, q1, p2);
  int o2 = orientation(p1, q1, q2);
  int o3 = orientation(p2, q2, p1);
  int o4 = orientation(p2, q2, q1);

  // General case
  if (o1 != o2 && o3 != o4)
    return true;

  // Special Cases
  // p1, q1 and p2 are collinear and p2 lies on segment p1q1
  if (o1 == 0 && onSegment(p1, p2, q1))
    return true;

  // p1, q1 and q2 are collinear and q2 lies on segment p1q1
  if (o2 == 0 && onSegment(p1, q2, q1))
    return true;

  // p2, q2 and p1 are collinear and p1 lies on segment p2q2
  if (o3 == 0 && onSegment(p2, p1, q2))
    return true;

  // p2, q2 and q1 are collinear and q1 lies on segment p2q2
  if (o4 == 0 && onSegment(p2, q1, q2))
    return true;

  // Doesn't fall in any of the above cases
  return false;
}
// Function to find the intersection of a line segment with a circle
bool lineCircleIntersection(Point p1, Point p2, Point C1, int radius) {
  // Line segment p1p2
  double A = p2.x - p1.x;
  double B = p2.y - p1.y;
  double C = p1.x - C1.x;
  double D = p1.y - C1.y;

  double a = sq(A) + sq(B);
  double b = 2 * (A * C + B * D);
  double c = sq(C) + sq(D) - sq(radius);

  // Discriminant
  double discriminant = sq(b) - 4 * a * c;

  // No real solutions, line does not intersect the circle
  if (discriminant < 0) {
    return false;
  }

  // Compute the two possible intersection points using the quadratic formula
  discriminant = std::sqrt(discriminant);
  double t1 = (-b - discriminant) / (2 * a);
  double t2 = (-b + discriminant) / (2 * a);

  // Check if either of the intersection points lie on the segment
  bool intersection1 = (t1 >= 0 && t1 <= 1);
  bool intersection2 = (t2 >= 0 && t2 <= 1);

  return intersection1 || intersection2;
}
} // namespace GameLogic
