#include "draw.hpp"
#include <raylib.h>

Vector2 pointToVector2(GameLogic::Point point) {
  return Vector2{static_cast<float>(point.x), static_cast<float>(point.y)};
}

template <typename T> void drawShapeFromVertices(const T &t, Color color) {
  if (t.vertices.size() == 3) {
    DrawTriangle(pointToVector2(t.vertices[0]), pointToVector2(t.vertices[1]),
                 pointToVector2(t.vertices[2]), color);
  } else if (t.vertices.size() == 4) {
    int width = t.highestX - t.lowestX;
    int height = t.highestY - t.lowestY;
    DrawRectangle(t.lowestX, t.lowestY, width, height, color);
  } else {
    // Draw polygon
  }
}
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
                        const std::vector<GameLogic::Ship> &enemyShips,
                        const std::vector<GameLogic::Projectile> &projectiles) {
  DrawRectangle(0, 0, DisplayConstants::screenWidth,
                DisplayConstants::screenHeight, PURPLE);

  drawShapeFromVertices(player, BLUE);

  for (const auto &enemy : enemyShips) {
    drawShapeFromVertices(enemy, RED);
  }
  for (const auto &projectile : projectiles) {
    drawShapeFromVertices(projectile, ORANGE);
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
