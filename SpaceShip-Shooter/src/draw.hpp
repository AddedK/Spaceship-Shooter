#ifndef DRAW_HPP
#define DRAW_HPP
#include "GameLogic.hpp"
#include "Ship.hpp"
#include "raylib.h"

namespace DisplayConstants {
// Constants related to rendering to the screen
constexpr int screenWidth = 600;
constexpr int screenHeight = 800;
constexpr int titleFontSize = 30;
constexpr int instructionFontSize = 18;
}; // namespace DisplayConstants

void drawTitleScreen();
void drawGameplayScreen(const GameLogic::Ship &player,
                        const std::vector<GameLogic::Ship> &enemyShips);
void drawEndingScreen();
#endif
