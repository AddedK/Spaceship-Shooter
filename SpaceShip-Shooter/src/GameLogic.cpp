#include "GameLogic.hpp"
#include <iostream>

namespace GameLogic {

void GameState::handleKeyPress(KeyPress keyPress) {
  switch (keyPress) {
  case KeyPress::UP:
  case KeyPress::DOWN:
  case KeyPress::LEFT:
  case KeyPress::RIGHT:
    movePlayer(keyPress);
    break;
  default:
    // TODO
    break;
  }
}

void GameState::movePlayer(KeyPress keyPress) {

  switch (keyPress) {
  case KeyPress::UP:
    if (player.y_position > 0) {
      --player.y_position;
      std::cout << "Moved player up to: " << player.y_position << std::endl;
    }
    break;
  case KeyPress::DOWN:
    if (player.y_position + player.height < screenHeight) {
      ++player.y_position;
      std::cout << "Moved player down to: " << player.y_position << std::endl;
    }
    break;
  case KeyPress::LEFT:
    if (player.x_position > 0) {
      --player.x_position;
      std::cout << "Moved player left to: " << player.x_position << std::endl;
    }
    break;
  case KeyPress::RIGHT:
    if (player.x_position + player.width < screenWidth) {
      ++player.x_position;
      std::cout << "Moved player right to: " << player.x_position << std::endl;
    }
    break;
  default:
    // TODO
    break;
  }
}

void GameState::setPlayer(Ship player) { this->player = player; }
void GameState::setDimensions(int screenWidth, int screenHeight) {
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
}
} // namespace GameLogic
