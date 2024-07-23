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
  DrawRectangle(0, 0, DisplayConstants::mainScreenWidth,
                DisplayConstants::mainScreenHeight, GREEN);

  const int titleXMiddle = (DisplayConstants::mainScreenWidth / 2) -
                           (4 * DisplayConstants::titleFontSize);
  const int titleYPosition = DisplayConstants::mainScreenHeight / 12;
  DrawText("TITLE SCREEN", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, DARKGREEN);

  const int instructionXPosition = (DisplayConstants::mainScreenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("PRESS ENTER or TAP to go to GAMEPLAY SCREEN", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKGREEN);
}

void drawGameplayScreen(const GameLogic::Ship &player,
                        const std::vector<GameLogic::Ship> &enemyShips,
                        const std::vector<GameLogic::Projectile> &projectiles) {
  DrawRectangle(0, 0, DisplayConstants::gameplayScreenWidth,
                DisplayConstants::gameplayScreenHeight, BLACK);

  drawShapeFromVertices(player, BLUE);

  Color enemyShipColor;
  for (const auto &enemy : enemyShips) {
    switch (enemy.shipType) {
    case GameLogic::ShipType::ULTIMATE:
      enemyShipColor = MAGENTA;
      break;
    case GameLogic::ShipType::STRIKER:
      enemyShipColor = BEIGE;
      break;
    case GameLogic::ShipType::ADVANCED:
      enemyShipColor = DARKGREEN;
      break;
    default:
      enemyShipColor = RED;

      break;
    }
    drawShapeFromVertices(enemy, enemyShipColor);
  }
  for (const auto &projectile : projectiles) {
    Color projectileColor;
    if (projectile.isHoming) {
      projectileColor = MAROON;
    } else {
      projectileColor = ORANGE;
    }
    drawShapeFromVertices(projectile, projectileColor);
  }

  const int titleXMiddle = (DisplayConstants::gameplayScreenWidth / 2) -
                           (6 * DisplayConstants::titleFontSize);
  const int titleYPosition = 10;
  DrawText("GAMEPLAY SCREEN", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, MAROON);

  const int instructionXPosition = 10;
  const int instructionYPosition = DisplayConstants::gameplayScreenHeight -
                                   2 * DisplayConstants::instructionFontSize;
  DrawText("PRESS Q to go to ENDING SCREEN", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize, MAROON);
  drawGameInfoBox();
}

void drawGameInfoBox() {
  // TODO

  DrawRectangle(DisplayConstants::gameplayScreenWidth, 0,
                DisplayConstants::gameInfoScreenWidth,
                DisplayConstants::gameInfoScreenHeight, YELLOW);
}

void drawEndingScreen() {
  DrawRectangle(0, 0, DisplayConstants::gameplayScreenWidth,
                DisplayConstants::gameplayScreenHeight, BLUE);

  const int titleXMiddle = (DisplayConstants::gameplayScreenWidth / 2) -
                           (5 * DisplayConstants::titleFontSize);
  const int titleYPosition = 10;
  DrawText("ENDING SCREEN", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, DARKBLUE);

  const int instructionXPosition = (DisplayConstants::gameplayScreenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("PRESS ENTER to RETURN to TITLE SCREEN", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKBLUE);
}
