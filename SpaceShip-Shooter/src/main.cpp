#include "GameLogic.hpp"
#include "raylib.h"
#include <optional>
#include <vector>

using namespace std;

enum class GameScreen { TITLE, GAMEPLAY, ENDING };

void inline drawTitleScreen(const int screenWidth, const int screenHeight) {
  DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
  DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
  DrawText("PRESS ENTER or TAP to go to GAMEPLAY SCREEN", 120, 220, 20,
           DARKGREEN);
}

void inline drawGameplayScreen(const int screenWidth, const int screenHeight,
                               const GameLogic::PlayerState player) {
  DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
  DrawRectangle(player.x_position, player.y_position, 50, 50, RED);
  DrawText("GAMEPLAY SCREEN", 10, 10, 20, MAROON);
  DrawText("PRESS Q to go to ENDING SCREEN", 400, 10, 20, MAROON);
}

void inline drawEndingScreen(const int screenWidth, const int screenHeight) {
  DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
  DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
  DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
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
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Spaceship Shooter");

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
      // TODO: Update TITLE screen variables here!

      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        game.setPlayer({100, 100});
        currentScreen = GameScreen::GAMEPLAY;
      }
    } break;
    case GameScreen::GAMEPLAY: {
      // TODO: Update GAMEPLAY screen variables here!

      auto keyPresses = keyPressToGameKeyPress();
      for (auto &keyPress : keyPresses) {
        game.handleKeyPress(keyPress);
      }

      if (IsKeyPressed(KEY_Q)) {
        currentScreen = GameScreen::ENDING;
      }
    } break;
    case GameScreen::ENDING: {
      // TODO: Update ENDING screen variables here!

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
      drawTitleScreen(screenWidth, screenHeight);

    } break;
    case GameScreen::GAMEPLAY: {
      drawGameplayScreen(screenWidth, screenHeight, game.getPlayer());

    } break;
    case GameScreen::ENDING: {
      drawEndingScreen(screenWidth, screenHeight);

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
