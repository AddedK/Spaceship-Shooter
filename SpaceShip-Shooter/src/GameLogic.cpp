#include "GameLogic.hpp"
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
  default:
    // TODO
    break;
  }
}

void GameState::movePlayer(MoveDirection direction) {
  // TODO: Allow special behavior for moving player
  moveShip(player, direction);
}

void GameState::setPlayer(Ship player) { this->player = player; }
void GameState::setDimensions(int screenWidth, int screenHeight) {
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
}
void GameState::addEnemyShip(Ship &&enemy) {
  this->enemyShips.push_back(enemy);
}
void GameState::clearEnemyShips() { this->enemyShips.clear(); }
void GameState::moveShip(Ship &ship, MoveDirection direction) {
  switch (direction) {
  case MoveDirection::UP:
    if (ship.y_position > 0) {
      --ship.y_position;
    }
    break;
  case MoveDirection::DOWN:
    if (ship.y_position + ship.height < screenHeight) {
      ++ship.y_position;
    }
    break;
  case MoveDirection::LEFT:
    if (ship.x_position > 0) {
      --ship.x_position;
    }
    break;
  case MoveDirection::RIGHT:
    if (ship.x_position + ship.width < screenWidth) {
      ++ship.x_position;
    }
    break;
  default:
    // TODO
    break;
  }
}
void GameState::update() { moveAllEnemies(); }
void GameState::moveAllEnemies() {
  // TODO: Now it just moves all enemies down
  for (auto &enemyShip : enemyShips) {
    moveShip(enemyShip, MoveDirection::DOWN);
  }
}
} // namespace GameLogic
