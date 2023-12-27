#include "draw.hpp"
#include "Ship.hpp"
#include <raylib.h>

void drawTitleScreen(const DisplayConstants &displayConstants) {
  DrawRectangle(0, 0, displayConstants.screenWidth,
                displayConstants.screenHeight, GREEN);

  const int titleXMiddle =
      (displayConstants.screenWidth / 2) - (4 * displayConstants.titleFontSize);
  const int titleYPosition = 20;
  DrawText("TITLE SCREEN", titleXMiddle, titleYPosition,
           displayConstants.titleFontSize, DARKGREEN);

  const int instructionXPosition = (displayConstants.screenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("PRESS ENTER or TAP to go to GAMEPLAY SCREEN", instructionXPosition,
           instructionYPosition, displayConstants.instructionFontSize,
           DARKGREEN);
}

void drawGameplayScreen(const DisplayConstants &displayConstants,
                        const GameLogic::Ship &player,
                        const std::vector<GameLogic::Ship> &enemyShips) {
  DrawRectangle(0, 0, displayConstants.screenWidth,
                displayConstants.screenHeight, PURPLE);
  DrawRectangle(player.x_position, player.y_position, player.width,
                player.height, BLUE);

  for (const auto &enemy : enemyShips) {
    DrawRectangle(enemy.x_position, enemy.y_position, enemy.width, enemy.height,
                  RED);
  }

  const int titleXMiddle =
      (displayConstants.screenWidth / 2) - (6 * displayConstants.titleFontSize);
  const int titleYPosition = 10;
  DrawText("GAMEPLAY SCREEN", titleXMiddle, titleYPosition,
           displayConstants.titleFontSize, MAROON);

  const int instructionXPosition = 10;
  const int instructionYPosition =
      displayConstants.screenHeight - 2 * displayConstants.instructionFontSize;
  DrawText("PRESS Q to go to ENDING SCREEN", instructionXPosition,
           instructionYPosition, displayConstants.instructionFontSize, MAROON);
}

void drawEndingScreen(const DisplayConstants &displayConstants) {
  DrawRectangle(0, 0, displayConstants.screenWidth,
                displayConstants.screenHeight, BLUE);

  const int titleXMiddle =
      (displayConstants.screenWidth / 2) - (5 * displayConstants.titleFontSize);
  const int titleYPosition = 10;
  DrawText("ENDING SCREEN", titleXMiddle, titleYPosition,
           displayConstants.titleFontSize, DARKBLUE);

  const int instructionXPosition = (displayConstants.screenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("PRESS ENTER to RETURN to TITLE SCREEN", instructionXPosition,
           instructionYPosition, displayConstants.instructionFontSize,
           DARKBLUE);
}
