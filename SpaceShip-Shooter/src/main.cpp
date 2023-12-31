#include "GameLogic.hpp"
#include "Ship.hpp"
#include "draw.hpp"
#include "raylib.h"
#include <optional>
#include <vector>

using namespace std;

enum class GameScreen { TITLE, GAMEPLAY, ENDING };

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
  if (IsKeyDown(KEY_SPACE)) {
    keyPresses.push_back(GameLogic::KeyPress::SPACE);
  }
  if (IsKeyDown(KEY_Q)) {
    keyPresses.push_back(GameLogic::KeyPress::Q);
  }
  return keyPresses;
}

int main(void) {

  // Setup raylib window
  InitWindow(DisplayConstants::screenWidth, DisplayConstants::screenHeight,
             "Spaceship Shooter");
  GameScreen currentScreen = GameScreen::TITLE;
  int framesCounter = 0; // Useful to count frames
  SetTargetFPS(60);      // Set desired framerate (frames-per-second)

  GameLogic::GameState game(DisplayConstants::screenWidth,
                            DisplayConstants::screenHeight);
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    switch (currentScreen) {
    case GameScreen::TITLE: {

      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        game.startGame();

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
      } else {
        game.update();
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

    switch (currentScreen) {
    case GameScreen::TITLE: {
      drawTitleScreen();

    } break;
    case GameScreen::GAMEPLAY: {
      drawGameplayScreen(game.getPlayer(), game.getEnemyShips());

    } break;
    case GameScreen::ENDING: {
      drawEndingScreen();

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
