#include "draw.hpp"
#include "Ship.hpp"
#include <raylib.h>

void drawTitleScreen() {
  DrawRectangle(0, 0, DisplayConstants::screenWidth,
                DisplayConstants::screenHeight, GREEN);

  const int titleXMiddle = (DisplayConstants::screenWidth / 2) -
                           (4 * DisplayConstants::titleFontSize);
  const int titleYPosition = 20;
  DrawText("TITLE SCREEN", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, DARKGREEN);

  const int instructionXPosition = (DisplayConstants::screenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("PRESS ENTER or TAP to go to GAMEPLAY SCREEN", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKGREEN);
}

void drawGameplayScreen(const GameLogic::Ship &player,
                        const std::vector<GameLogic::Ship> &enemyShips) {
  DrawRectangle(0, 0, DisplayConstants::screenWidth,
                DisplayConstants::screenHeight, PURPLE);
  DrawRectangle(player.x_position, player.y_position, player.width,
                player.height, BLUE);

  for (const auto &enemy : enemyShips) {
    DrawRectangle(enemy.x_position, enemy.y_position, enemy.width, enemy.height,
                  RED);
  }

  const int titleXMiddle = (DisplayConstants::screenWidth / 2) -
                           (6 * DisplayConstants::titleFontSize);
  const int titleYPosition = 10;
  DrawText("GAMEPLAY SCREEN", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, MAROON);

  const int instructionXPosition = 10;
  const int instructionYPosition = DisplayConstants::screenHeight -
                                   2 * DisplayConstants::instructionFontSize;
  DrawText("PRESS Q to go to ENDING SCREEN", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize, MAROON);
}

void drawEndingScreen() {
  DrawRectangle(0, 0, DisplayConstants::screenWidth,
                DisplayConstants::screenHeight, BLUE);

  const int titleXMiddle = (DisplayConstants::screenWidth / 2) -
                           (5 * DisplayConstants::titleFontSize);
  const int titleYPosition = 10;
  DrawText("ENDING SCREEN", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, DARKBLUE);

  const int instructionXPosition = (DisplayConstants::screenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("PRESS ENTER to RETURN to TITLE SCREEN", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKBLUE);
}
