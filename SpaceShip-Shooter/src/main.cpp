#include "GameLogic.hpp"
#include "draw.hpp"
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

  // Setup raylib window
  InitWindow(displayConstants.screenWidth, displayConstants.screenHeight,
             "Spaceship Shooter");
  GameScreen currentScreen = GameScreen::TITLE;
  int framesCounter = 0; // Useful to count frames
  SetTargetFPS(60);      // Set desired framerate (frames-per-second)

  GameLogic::GameState game(displayConstants.screenWidth,
                            displayConstants.screenHeight);
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    switch (currentScreen) {
    case GameScreen::TITLE: {

      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        game.setPlayer({gameConstants.playerStartingX,
                        gameConstants.playerStartingY,
                        gameConstants.playerWidth, gameConstants.playerHeight});
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
