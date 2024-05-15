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
  switch (direction) {
  case MoveDirection::UP:
    ship.yPosition -= ship.movementSpeed;
    if (ship.yPosition < 0) {
      ship.yPosition = 0;
    }
    break;
  case MoveDirection::DOWN:
    ship.yPosition += ship.movementSpeed;
    if (ship.yPosition + ship.height > screenHeight) {
      ship.yPosition = screenHeight - ship.height;
    }
    break;
  case MoveDirection::LEFT:
    ship.xPosition -= ship.movementSpeed;
    if (ship.xPosition < 0) {
      ship.xPosition = 0;
    }
    break;
  case MoveDirection::RIGHT:
    ship.xPosition += ship.movementSpeed;
    if (ship.xPosition + ship.width > screenWidth) {
      ship.xPosition = screenWidth - ship.width;
    }
    break;
  default:
    // TODO
    break;
  }
}
void GameState::updateGame() {
  ++frameNumber;
  if (getPlayerAliveStatus()) {
    moveAllEnemies();
    moveAllProjectiles();
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
  player.setNrOfLives(player.nrOfLives - 1);
  if (player.nrOfLives <= 0) {
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
      begin->nrOfLives--;
      if (begin->nrOfLives == 0) {
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
      bool shouldAdvanceIterator = true;
      for (auto shipIterator = enemyShips.begin();
           shipIterator != enemyShips.end();) {
        if (isColliding(*shipIterator, *projectileIterator)) {
          shipIterator->nrOfLives--;
          if (shipIterator->nrOfLives == 0) {
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

} // namespace GameLogic
