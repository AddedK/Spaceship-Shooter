#ifndef DRAW_HPP
#define DRAW_HPP
#include "GameLogic.hpp"
#include "raylib.h"

struct DisplayConstants {
  // Constants related to rendering to the screen
  const int screenWidth = 600;
  const int screenHeight = 800;
  const int titleFontSize = 30;
  const int instructionFontSize = 18;
};

void drawTitleScreen(const DisplayConstants &displayConstants);
void drawGameplayScreen(const DisplayConstants &displayConstants,
                        const GameLogic::Ship player);
void drawEndingScreen(const DisplayConstants &displayConstants);
#endif
