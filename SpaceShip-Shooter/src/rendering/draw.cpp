#include "draw.hpp"
#include <raylib.h>
#include <string>

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
    // TODO: Draw polygon
  }
}
void drawStar(int centerX, int centerY) {
  int point1Y = centerY - 5; // Top point
  int point1X = centerX;
  int point2Y = point1Y + 2;
  int point2X = point1X - 1;
  int point3Y = point2Y + 1;
  int point3X = point2X - 2; // Leftmost point
  int point4Y = point3Y + 2;
  int point4X = point3X + 2;
  int point5Y = point4Y + 2;
  int point5X = point4X - 1;
  int point6Y = point5Y - 2;
  int point6X = point1X;
  int point7Y = point5Y;
  int point7X = point6X + (point6X - point5X);
  int point8Y = point4Y;
  int point8X = point7X - (point4X - point5X);
  int point9Y = point3Y; // Rightmost point
  int point9X = point8X + (point4X - point3X);
  int point10Y = point2Y;
  int point10X = point9X - (point2X - point3X);

  DrawLine(point1X, point1Y, point2X, point2Y, WHITE);
  DrawLine(point2X, point2Y, point3X, point3Y, WHITE);
  DrawLine(point3X, point3Y, point4X, point4Y, WHITE);
  DrawLine(point4X, point4Y, point5X, point5Y, WHITE);
  DrawLine(point5X, point5Y, point6X, point6Y, WHITE);
  DrawLine(point6X, point6Y, point7X, point7Y, WHITE);
  DrawLine(point7X, point7Y, point8X, point8Y, WHITE);
  DrawLine(point8X, point8Y, point9X, point9Y, WHITE);
  DrawLine(point9X, point9Y, point10X, point10Y, WHITE);
  DrawLine(point10X, point10Y, point1X, point1Y, WHITE);
}

void drawTitleScreen() {
  DrawRectangle(0, 0, DisplayConstants::mainScreenWidth,
                DisplayConstants::mainScreenHeight, GREEN);

  const std::string title = "SPACESHIP SHOOTER";
  const int titleStartPositionX = 220;
  const int titleYPosition = 10;
  DrawText(title.c_str(), titleStartPositionX, titleYPosition,
           DisplayConstants::titleFontSize, DARKGREEN);

  const int instructionXPosition = 150;
  const int instructionYPosition = 220;
  DrawText("Press ENTER play the game", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKGREEN);
  DrawText("Press H for help", instructionXPosition, instructionYPosition + 200,
           DisplayConstants::instructionFontSize, DARKGREEN);
}

void drawHelpScreen() {

  DrawRectangle(0, 0, DisplayConstants::mainScreenWidth,
                DisplayConstants::mainScreenHeight, GREEN);

  const std::string title = "HELP";
  const int titleStartPositionX = 340;
  const int titleYPosition = 10;
  DrawText(title.c_str(), titleStartPositionX, titleYPosition,
           DisplayConstants::titleFontSize, DARKGREEN);

  const int instructionXPosition = 150;
  const int instructionYPosition = 640;
  DrawText("Get score by surviving and destroying enemy ships.",
           instructionXPosition, 100, DisplayConstants::instructionFontSize,
           DARKGREEN);
  std::vector<GameLogic::Point> BasicShipPoints;
  BasicShipPoints.push_back(GameLogic::Point{200, 140});
  BasicShipPoints.push_back(GameLogic::Point{230, 170});
  BasicShipPoints.push_back(GameLogic::Point{260, 140});
  GameLogic::Ship enemyShip(BasicShipPoints, 1, 1, 1,
                            GameLogic::ShipType::BASIC);
  drawShapeFromVertices(enemyShip, RED);
  DrawText("<---- This is a basic enemy ship.", 300, 150,
           DisplayConstants::instructionFontSize, DARKGREEN);

  DrawText("You lose when when you run out of lives.", instructionXPosition,
           200, DisplayConstants::instructionFontSize, DARKGREEN);

  DrawText("Press the arrow keys to move the player ship.",
           instructionXPosition, 300, DisplayConstants::instructionFontSize,
           DARKGREEN);

  DrawText("Press SPACEBAR to shoot a projectile.", instructionXPosition, 400,
           DisplayConstants::instructionFontSize, DARKGREEN);

  DrawText("Pick up boons to improve your ship.", instructionXPosition, 500,
           DisplayConstants::instructionFontSize, DARKGREEN);
  GameLogic::Point boonCenter({instructionXPosition + 50, 580});
  DrawCircle(boonCenter.x, boonCenter.y, 10, SKYBLUE);
  DrawText("<--- This is how one of the boons look like.",
           instructionXPosition + 100, 570,
           DisplayConstants::instructionFontSize, DARKGREEN);

  DrawText("Press ENTER to return to the MAIN menu", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKGREEN);
}

void drawRandomWhiteBackgroundStars(int frameNumber) {
  drawStar(1 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 15) % DisplayConstants::gameplayScreenHeight);
  drawStar(1 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 290) % DisplayConstants::gameplayScreenHeight);

  drawStar(3 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 20) % DisplayConstants::gameplayScreenHeight);
  drawStar(3 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 320) % DisplayConstants::gameplayScreenHeight);

  drawStar(5 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 47) % DisplayConstants::gameplayScreenHeight);
  drawStar(5 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 277) % DisplayConstants::gameplayScreenHeight);

  drawStar(7 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 10) % DisplayConstants::gameplayScreenHeight);
  drawStar(7 * DisplayConstants::gameplayScreenWidth / 8,
           (4 * frameNumber + 380) % DisplayConstants::gameplayScreenHeight);
}

void drawGameplayScreen(const GameLogic::Ship &player,
                        const std::vector<GameLogic::Ship> &enemyShips,
                        const std::vector<GameLogic::Projectile> &projectiles,
                        const std::vector<GameLogic::Upgrade> &upgrades,
                        int playerScore, int gameDifficulty, int frameNumber) {

  DrawRectangle(0, 0, DisplayConstants::gameplayScreenWidth,
                DisplayConstants::gameplayScreenHeight, BLACK);

  drawRandomWhiteBackgroundStars(frameNumber);

  Color upgradeColor;
  for (auto upgrade : upgrades) {
    switch (upgrade.upgradeType) {
    case GameLogic::UpgradeType::MOVEMENTSPEED:
      upgradeColor = ORANGE;
      break;
    case GameLogic::UpgradeType::BONUSLIFE:
      upgradeColor = YELLOW;
      break;
    case GameLogic::UpgradeType::PROJECTILESPEED:
      upgradeColor = SKYBLUE;
      break;
    default:
      upgradeColor = RED;

      break;
    }
    DrawCircle(upgrade.center.x, upgrade.center.y, upgrade.radius,
               upgradeColor);
  }

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

  const int instructionXPosition = 10;
  const int instructionYPosition = DisplayConstants::gameplayScreenHeight -
                                   2 * DisplayConstants::instructionFontSize;
  DrawText("Press Q to go to the ENDING screen.", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize, MAROON);
  drawGameInfoBox(player.getNrOfLives(), playerScore, gameDifficulty);
}

void drawGameInfoBox(int playerLives, int playerScore, int gameDifficulty) {

  DrawRectangle(DisplayConstants::gameplayScreenWidth, 0,
                DisplayConstants::gameInfoScreenWidth,
                DisplayConstants::gameInfoScreenHeight, GRAY);
  DrawText("SCORE", DisplayConstants::gameplayScreenWidth + 10, 10,
           DisplayConstants::instructionFontSize, BLUE);
  DrawText(std::to_string(playerScore).c_str(),
           DisplayConstants::gameplayScreenWidth + 20, 35,
           DisplayConstants::instructionFontSize, BLUE);

  DrawText("LIVES", DisplayConstants::gameplayScreenWidth + 10, 60,
           DisplayConstants::instructionFontSize, BLUE);
  DrawText(std::to_string(playerLives).c_str(),
           DisplayConstants::gameplayScreenWidth + 20, 85,
           DisplayConstants::instructionFontSize, BLUE);
  DrawText("DIFFICULTY", DisplayConstants::gameplayScreenWidth + 2, 115,
           DisplayConstants::instructionFontSize - 6, BLUE);
  DrawText(std::to_string(gameDifficulty).c_str(),
           DisplayConstants::gameplayScreenWidth + 20, 130,
           DisplayConstants::instructionFontSize, BLUE);
}

void drawEndingScreen() {
  DrawRectangle(0, 0, DisplayConstants::gameplayScreenWidth,
                DisplayConstants::gameplayScreenHeight, BLUE);

  const int titleXMiddle = 240;
  const int titleYPosition = 10;
  DrawText("GAME OVER", titleXMiddle, titleYPosition,
           DisplayConstants::titleFontSize, DARKBLUE);

  const int instructionXPosition = (DisplayConstants::gameplayScreenWidth / 6);
  const int instructionYPosition = 220;
  DrawText("Press ENTER to return to the main menu.", instructionXPosition,
           instructionYPosition, DisplayConstants::instructionFontSize,
           DARKBLUE);
}
