#include "GameLogic.hpp"
#include "raylib.h"
#include <optional>
#include <vector>

using namespace std;

enum class GameScreen { TITLE, GAMEPLAY, ENDING };

struct GameConstants {
  // Constants related to game logic
  const int playerStartingX = 100;
  const int playerStartingY = 100;
  const int playerWidth = 50;
  const int playerHeight = 50;
};

struct DisplayConstants {
  // Constants related to rendering to the screen
  const int screenWidth = 600;
  const int screenHeight = 800;
  const int titleFontSize = 30;
  const int instructionFontSize = 18;
};

void inline drawTitleScreen(const DisplayConstants &displayConstants) {
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

void inline drawGameplayScreen(const DisplayConstants &displayConstants,
                               const GameLogic::PlayerState player) {
  DrawRectangle(0, 0, displayConstants.screenWidth,
                displayConstants.screenHeight, PURPLE);
  DrawRectangle(player.x_position, player.y_position, player.width,
                player.height, RED);

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

void inline drawEndingScreen(const DisplayConstants &displayConstants) {
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

vector<GameLogic::KeyPress> keyPressToGameKeyPress() {
  vector<GameLogic::KeyPress> keyPresses;
  if (IsKeyDown(KEY_UP)) {
    keyPresses.push_back(GameLogic::KeyPress::UP);
  }
  if (IsKeyDown(KEY_DOWN)) {
    keyPresses.push_back(GameLogic::KeyPress::DOWN);
  }
  if (IsKeyDown(KEY_LEFT)) {
    keyPresses.push_back(GameLogic::KeyPress::LEFT);
  }
  if (IsKeyDown(KEY_RIGHT)) {
    keyPresses.push_back(GameLogic::KeyPress::RIGHT);
  }
  if (IsKeyDown(KEY_ENTER)) {
    keyPresses.push_back(GameLogic::KeyPress::ENTER);
  }
  if (IsKeyDown(KEY_Q)) {
    keyPresses.push_back(GameLogic::KeyPress::Q);
  }
  return keyPresses;
}

int main(void) {
  constexpr GameConstants gameConstants;
  constexpr DisplayConstants displayConstants;

  InitWindow(displayConstants.screenWidth, displayConstants.screenHeight,
             "Spaceship Shooter");

  GameScreen currentScreen = GameScreen::TITLE;

  // TODO: Initialize all required variables and load all required data
  // here!

  int framesCounter = 0; // Useful to count frames

  SetTargetFPS(60); // Set desired framerate (frames-per-second)

  GameLogic::GameState game;

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    switch (currentScreen) {
    case GameScreen::TITLE: {

      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        game.setPlayer({gameConstants.playerStartingX,
                        gameConstants.playerStartingY,
                        gameConstants.playerWidth, gameConstants.playerHeight});
        game.setDimensions(displayConstants.screenWidth,
                           displayConstants.screenHeight);
        currentScreen = GameScreen::GAMEPLAY;
      }
    } break;
    case GameScreen::GAMEPLAY: {

      auto keyPresses = keyPressToGameKeyPress();
      for (auto &keyPress : keyPresses) {
        game.handleKeyPress(keyPress);
      }

      if (IsKeyPressed(KEY_Q)) {
        currentScreen = GameScreen::ENDING;
      }
    } break;
    case GameScreen::ENDING: {

      if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GameScreen::TITLE;
      }
    } break;
    default:
      break;
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (currentScreen) {
    case GameScreen::TITLE: {
      drawTitleScreen(displayConstants);

    } break;
    case GameScreen::GAMEPLAY: {
      drawGameplayScreen(displayConstants, game.getPlayer());

    } break;
    case GameScreen::ENDING: {
      drawEndingScreen(displayConstants);

    } break;
    default:
      break;
    }

    EndDrawing();
  }

  // TODO: Unload all loaded data (textures, fonts, audio) here!

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
