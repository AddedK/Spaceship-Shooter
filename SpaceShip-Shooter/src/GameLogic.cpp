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
    if (player.y_position > 0) { // TODO magic number
      --player.y_position;
      std::cout << "Moved player up to: " << player.y_position << std::endl;
    }
    break;
  case KeyPress::DOWN:
    if (player.y_position < 450) { // TODO magic number
      ++player.y_position;
      std::cout << "Moved player down to: " << player.y_position << std::endl;
    }
    break;
  case KeyPress::LEFT:
    if (player.x_position > 0) { // TODO magic number
      --player.x_position;
      std::cout << "Moved player left to: " << player.x_position << std::endl;
    }
    break;
  case KeyPress::RIGHT:
    if (player.x_position < 850) { // TODO magic number
      ++player.x_position;
      std::cout << "Moved player right to: " << player.x_position << std::endl;
    }
    break;
  default:
    // TODO
    break;
  }
}

void GameState::setPlayer(PlayerState player) { this->player = player; }
} // namespace GameLogic
