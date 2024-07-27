#include "game_logic/GameLogic.hpp"
#include "raylib.h"
#include "rendering/draw.hpp"
#include <chrono>
#include <vector>

using namespace std;

enum class GameScreen { TITLE, HELP, GAMEPLAY, ENDING };

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
  if (IsKeyPressed(KEY_SPACE)) {
    keyPresses.push_back(GameLogic::KeyPress::SPACE);
  }
  if (IsKeyDown(KEY_Q)) {
    keyPresses.push_back(GameLogic::KeyPress::Q);
  }
  return keyPresses;
}

int main(void) {
  auto lastCallTimeTitle =
      std::chrono::steady_clock::now() - std::chrono::seconds(10);
  auto lastCallTimeHelp =
      std::chrono::steady_clock::now() - std::chrono::seconds(10);
  auto lastCallTimeEnding =
      std::chrono::steady_clock::now() - std::chrono::seconds(10);
  const int requiredDelay = 5; // Delay in seconds
  // Setup raylib window
  // Note: there is no straight forward way of disabling resizing and
  // fullscreen. Despite resizing being seemingly off by default, it is still
  // possible.
  InitWindow(DisplayConstants::mainScreenWidth,
             DisplayConstants::mainScreenHeight, "Spaceship Shooter");
  GameScreen currentScreen = GameScreen::TITLE;
  constexpr int FPS = 60;
  SetTargetFPS(FPS); // Set desired framerate (frames-per-second)

  GameLogic::GameState game(FPS, DisplayConstants::gameplayScreenWidth,
                            DisplayConstants::gameplayScreenHeight);
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    switch (currentScreen) {
    case GameScreen::TITLE: {

      if (IsKeyPressed(KEY_ENTER)) {
        game.startGame();
        currentScreen = GameScreen::GAMEPLAY;
      } else if (IsKeyPressed(KEY_H)) {
        currentScreen = GameScreen::HELP;
      }
      break;
    }
    case GameScreen::HELP: {
      if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GameScreen::TITLE;
      }
      break;
    }
    case GameScreen::GAMEPLAY: {
      auto keyPresses = keyPressToGameKeyPress();
      for (auto &keyPress : keyPresses) {
        game.handleKeyPress(keyPress);
      }

      if (IsKeyPressed(KEY_Q)) {
        currentScreen = GameScreen::ENDING;
      } else {
        game.updateGame();
      }
      if (!game.getPlayerAliveStatus()) {
        currentScreen = GameScreen::ENDING;
      } else {
        break;
      }
    }
    case GameScreen::ENDING: {

      if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GameScreen::TITLE;
      }
      break;
    }
    default:
      break;
    }
    BeginDrawing();

    switch (currentScreen) {
    case GameScreen::TITLE: {
      auto now = std::chrono::steady_clock::now();
      auto durationSinceLastCall =
          std::chrono::duration_cast<std::chrono::seconds>(now -
                                                           lastCallTimeTitle)
              .count();
      if (durationSinceLastCall >= requiredDelay) {
        drawTitleScreen();
        lastCallTimeTitle = now;
        lastCallTimeHelp = now - std::chrono::seconds(10);
        lastCallTimeEnding = now - std::chrono::seconds(10);
      }
      break;
    }
    case GameScreen::HELP: {
      auto now = std::chrono::steady_clock::now();
      auto durationSinceLastCall =
          std::chrono::duration_cast<std::chrono::seconds>(now -
                                                           lastCallTimeHelp)
              .count();
      if (durationSinceLastCall >= requiredDelay) {
        drawHelpScreen();
        lastCallTimeHelp = now;
        lastCallTimeTitle = now - std::chrono::seconds(10);
        lastCallTimeEnding = now - std::chrono::seconds(10);
      }
      break;
    }
    case GameScreen::GAMEPLAY: {
      drawGameplayScreen(game.getPlayer(), game.getEnemyShips(),
                         game.getProjectiles(), game.getUpgrades(),
                         game.getPlayerScore(), game.getGameDifficulty(),
                         game.getFrameNumber());
      break;
    }
    case GameScreen::ENDING: {
      auto now = std::chrono::steady_clock::now();
      auto durationSinceLastCall =
          std::chrono::duration_cast<std::chrono::seconds>(now -
                                                           lastCallTimeEnding)
              .count();
      if (durationSinceLastCall >= requiredDelay) {
        drawEndingScreen();
        lastCallTimeEnding = now;
        lastCallTimeTitle = now - std::chrono::seconds(10);
        lastCallTimeHelp = now - std::chrono::seconds(10);
      }
      break;
    }
    default:
      break;
    }

    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
