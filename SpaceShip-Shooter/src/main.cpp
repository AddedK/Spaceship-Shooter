#include "raylib.h"

enum class GameScreen { TITLE, GAMEPLAY, ENDING };

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Spaceship Shooter");

  GameScreen currentScreen = GameScreen::TITLE;

  // TODO: Initialize all required variables and load all required data here!

  int framesCounter = 0; // Useful to count frames

  SetTargetFPS(60); // Set desired framerate (frames-per-second)

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    switch (currentScreen) {
    case GameScreen::TITLE: {
      // TODO: Update TITLE screen variables here!

      // Press enter to change to GAMEPLAY screen
      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        currentScreen = GameScreen::GAMEPLAY;
      }
    } break;
    case GameScreen::GAMEPLAY: {
      // TODO: Update GAMEPLAY screen variables here!

      // Press Q to change to ENDING screen
      if (IsKeyPressed(KEY_Q)) {
        currentScreen = GameScreen::ENDING;
      }
    } break;
    case GameScreen::ENDING: {
      // TODO: Update ENDING screen variables here!

      // Press enter to return to TITLE screen
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
      // TODO: Draw TITLE screen here!
      DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
      DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
      DrawText("PRESS ENTER or TAP to go to GAMEPLAY SCREEN", 120, 220, 20,
               DARKGREEN);

    } break;
    case GameScreen::GAMEPLAY: {
      // TODO: Draw GAMEPLAY screen here!
      DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
      DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
      DrawText("PRESS Q to go to ENDING SCREEN", 130, 220, 20, MAROON);

    } break;
    case GameScreen::ENDING: {
      // TODO: Draw ENDING screen here!
      DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
      DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
      DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

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
