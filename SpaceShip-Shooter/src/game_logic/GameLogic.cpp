#include "GameLogic.hpp"
#include "gameEnums.hpp"
#include <iostream>
#include <map>

namespace GameLogic {

std::map<KeyPress, MoveDirection> keyToDirection = {
    {KeyPress::UP, MoveDirection::UP},
    {KeyPress::DOWN, MoveDirection::DOWN},
    {KeyPress::LEFT, MoveDirection::LEFT},
    {KeyPress::RIGHT, MoveDirection::RIGHT}};

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
              int screenHeight) {

  std::vector<Point> &vertices = ship.vertices;
  switch (direction) {
  case MoveDirection::UP: {
    int lowestY = screenHeight + 1;
    for (int i = 0; i < vertices.size(); ++i) {
      if (vertices[i].y < lowestY) {
        lowestY = vertices[i].y;
      }
    }
    int clippedMovement =
        (lowestY - ship.movementSpeed) < 0 ? lowestY : ship.movementSpeed;
    for (auto &point : vertices) {
      point.y -= clippedMovement;
    }
    break;
  }
  case MoveDirection::DOWN: {
    int highestY = 0;
    for (int i = 0; i < vertices.size(); ++i) {
      if (vertices[i].y > highestY) {
        highestY = vertices[i].y;
      }
    }
    int clippedMovement = (highestY + ship.movementSpeed) > screenHeight
                              ? screenHeight - highestY
                              : ship.movementSpeed;
    for (auto &point : vertices) {
      point.y += clippedMovement;
    }
    break;
  }
  case MoveDirection::LEFT: {
    int lowestX = 0;
    for (int i = 0; i < vertices.size(); ++i) {
      if (vertices[i].x < lowestX) {
        lowestX = vertices[i].x;
      }
    }
    int clippedMovement =
        (lowestX - ship.movementSpeed) < 0 ? lowestX : ship.movementSpeed;

    for (auto &point : vertices) {
      point.x -= clippedMovement;
    }
    break;
  }
  case MoveDirection::RIGHT: {
    int highestX = screenWidth + 1;
    for (int i = 0; i < vertices.size(); ++i) {
      if (vertices[i].x > highestX) {
        highestX = vertices[i].x;
      }
    }
    int clippedMovement = (highestX + ship.movementSpeed) > screenWidth
                              ? screenWidth - highestX
                              : ship.movementSpeed;
    for (auto &point : vertices) {
      point.x -= clippedMovement;
    }
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
    if (enemyShip.yPosition < screenHeight &&
        ((frameNumber - enemyShip.frameWhenLastFiredProjectile) >=
         GameConstants::enemyInitialFramesBetweenShots)) {
      int xPositionMiddle = (enemyShip.xPosition + enemyShip.width / 2);
      Projectile projectile(xPositionMiddle, enemyShip.yPosition + 1,
                            GameConstants::projectileDefaultWidth,
                            GameConstants::projectileDefaultHeight,
                            GameConstants::projectileDefaultSpeed,
                            MoveDirection::DOWN);

      addProjectile(std::move(projectile));
      enemyShip.frameWhenLastFiredProjectile = frameNumber;
    }
  }
  return;
}
void GameState::updateGame() {
  ++frameNumber;
  if (getPlayerAliveStatus()) {
    moveAllEnemies();
    moveAllProjectiles();
    allEnemiesShoot();
    checkAndHandleCollisions();
  } else {
    std::cout << "Player is dead!" << std::endl;
  }
}
void GameState::moveAllEnemies() {
  // TODO: Now it just moves all enemies down
  for (auto &enemyShip : enemyShips) {
    moveShip(enemyShip, MoveDirection::DOWN, screenWidth, screenHeight);
  }
}

void GameState::startGame() {
  setPlayerAliveStatus(true);
  setPlayer({screenWidth / 2 - GameConstants::playerWidth / 2,
             screenHeight - GameConstants::playerHeight,
             GameConstants::playerWidth, GameConstants::playerHeight,
             GameConstants::playerInitialSpeed,
             GameConstants::playerInitialNrOfLives});
  clearEnemyShips();
  removeAllProjectiles();
  Ship enemyShip(screenWidth / 2 - GameConstants::playerWidth / 2, 0,
                 GameConstants::playerWidth, GameConstants::playerHeight,
                 GameConstants::enemyInitialSpeed,
                 GameConstants::enemyInitialNrOfLives);
  addEnemyShip(std::move(enemyShip));
}

void GameState::addProjectile(Projectile &&projectile) {
  this->projectiles.push_back(projectile);
}
void GameState::addPlayerProjectile() {
  if (player.yPosition > 0 &&
          ((frameNumber - player.frameWhenLastFiredProjectile) >=
           GameConstants::playerInitialFramesBetweenShots) ||
      frameNumber == 0) {
    int xPositionMiddle = (player.xPosition + player.width / 2);
    Projectile projectile(xPositionMiddle, player.yPosition - 1,
                          GameConstants::projectileDefaultWidth,
                          GameConstants::projectileDefaultHeight,
                          GameConstants::projectileDefaultSpeed,
                          MoveDirection::UP);

    addProjectile(std::move(projectile));
    player.frameWhenLastFiredProjectile = frameNumber;
  }
}

void GameState::moveAllProjectiles() {
  // Remove all projectiles that are at the bottom or top
  for (auto begin = projectiles.begin(); begin != projectiles.end();) {
    if (begin->yPosition == 0 || begin->yPosition == screenHeight) {
      begin = projectiles.erase(begin);
    } else {
      moveProjectile(*begin, screenWidth, screenHeight);
      ++begin;
    }
  }
}

void moveProjectile(Projectile &projectile, int screenWidth, int screenHeight) {
  // Code duplication but it's okay
  switch (projectile.direction) {
  case MoveDirection::UP:
    projectile.yPosition -= projectile.movementSpeed;
    if (projectile.yPosition < 0) {
      projectile.yPosition = 0;
    }
    break;
  case MoveDirection::DOWN:
    projectile.yPosition += projectile.movementSpeed;
    if (projectile.yPosition + projectile.height > screenHeight) {
      projectile.yPosition = screenHeight - projectile.height;
    }
    break;
  case MoveDirection::LEFT:
    projectile.xPosition -= projectile.movementSpeed;
    if (projectile.xPosition < 0) {
      projectile.xPosition = 0;
    }
    break;
  case MoveDirection::RIGHT:
    projectile.xPosition += projectile.movementSpeed;
    if (projectile.xPosition + projectile.width > screenWidth) {
      projectile.xPosition = screenWidth - projectile.width;
    }
    break;
  default:
    // TODO
    break;
  }
}
void GameState::removeAllProjectiles() { this->projectiles.clear(); }

void GameState::setPlayerAliveStatus(bool status) {
  this->playerIsAlive = status;
}

void GameState::playerLosesLife() {
  player.decrementNrOfLives(1);
  if (player.getNrOfLives() <= 0) {
    std::cout << "Player lost a life and died" << std::endl;
    setPlayerAliveStatus(false);
  }
}

void GameState::playerAndShipCollisions() {
  if (!getPlayerAliveStatus()) {
    return;
  }
  for (auto begin = enemyShips.begin(); begin != enemyShips.end();) {
    if (isColliding(player, *begin)) {
      playerLosesLife();
      begin->decrementNrOfLives(1);
      if (begin->getNrOfLives() == 0) {
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
    if (getPlayerAliveStatus() && isColliding(player, *projectileIterator)) {
      playerLosesLife();
      projectileIterator = projectiles.erase(projectileIterator);
    } else {
      // Check if projectile hits another ship
      if (projectileIterator->direction == MoveDirection::DOWN) {
        ++projectileIterator;
        continue;
      }
      bool shouldAdvanceIterator = true;
      for (auto shipIterator = enemyShips.begin();
           shipIterator != enemyShips.end();) {
        if (isColliding(*shipIterator, *projectileIterator)) {
          shipIterator->decrementNrOfLives(1);
          if (shipIterator->getNrOfLives() == 0) {
            shipIterator = enemyShips.erase(shipIterator);
          } else {
            ++shipIterator;
          }
          projectileIterator = projectiles.erase(projectileIterator);
          shouldAdvanceIterator = false;
          break;
        } else {
          ++shipIterator;
        }
      }
      if (shouldAdvanceIterator) {
        ++projectileIterator;
      }
    }
  }
  return;
}

void GameState::checkAndHandleCollisions() {
  // Opinion: If two ships and a projectile are in the same spot and the ships
  // can destory each other, then only projectile goes unscathed
  playerAndShipCollisions();
  if (getPlayerAliveStatus()) {
    shipAndProjectileCollisions();
  }
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

bool lineIsIntersecting(const Point &p1, const Point &q1, const Point &p2,
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
} // namespace GameLogic
