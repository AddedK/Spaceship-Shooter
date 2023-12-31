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
void GameState::update() {
  ++frameNumber;
  frameNumber %= fps;
  moveAllEnemies();
  moveAllProjectiles();
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
             GameConstants::playerWidth, GameConstants::playerHeight});
  setPlayerSpeed(5);
  clearEnemyShips();
  removeAllProjectiles();
  Ship enemyShip(screenWidth / 2 - GameConstants::playerWidth / 2, 0,
                 GameConstants::playerWidth, GameConstants::playerHeight);
  addEnemyShip(std::move(enemyShip));
}

void GameState::addProjectile(Projectile &&projectile) {
  this->projectiles.push_back(projectile);
}
void GameState::addPlayerProjectile() {
  if (player.yPosition > 0 && frameNumber % (fps / 2) == 0) {
    int xPositionMiddle = (player.xPosition + player.width / 2);
    Projectile projectile(xPositionMiddle, player.yPosition - 1, 3, 3, 5,
                          MoveDirection::UP);

    addProjectile(std::move(projectile));
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

} // namespace GameLogic
