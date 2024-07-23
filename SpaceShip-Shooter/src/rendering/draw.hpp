#ifndef DRAW_HPP
#define DRAW_HPP
#include "../game_logic/Projectile.hpp"
#include "../game_logic/Ship.hpp"
#include "raylib.h"

namespace DisplayConstants {
// Constants related to rendering to the screen

constexpr int gameplayScreenWidth = 600;
constexpr int gameplayScreenHeight = 800;

constexpr int gameInfoScreenWidth = 80;
constexpr int gameInfoScreenHeight = gameplayScreenHeight;

constexpr int mainScreenWidth = gameplayScreenWidth + gameInfoScreenWidth;
constexpr int mainScreenHeight = gameplayScreenHeight;

constexpr int titleFontSize = 30;
constexpr int instructionFontSize = 18;
constexpr int gameInfoFontSize = 14;
}; // namespace DisplayConstants

void drawTitleScreen();
void drawGameplayScreen(const GameLogic::Ship &player,
                        const std::vector<GameLogic::Ship> &enemyShips,
                        const std::vector<GameLogic::Projectile> &projectiles,
                        int playerScore);
void drawGameInfoBox(int playerLives, int playerScore);
void drawEndingScreen();

Vector2 pointToVector2(GameLogic::Point point);
#endif
