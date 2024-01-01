#include "../src/GameLogic.hpp"
#include "../src/Ship.hpp"
#include "doctest.h"

TEST_CASE("Testing GameState Functionality ") {
  GameLogic::GameState gameState(60, 10, 10);
  REQUIRE(gameState.getEnemyShips().size() == 0);
  auto playerShip = gameState.getPlayer();
  REQUIRE(playerShip.xPosition == 0);
  REQUIRE(playerShip.yPosition == 0);
  REQUIRE(playerShip.width == 10);
  REQUIRE(playerShip.height == 10);
  REQUIRE(playerShip.movementSpeed == 1);

  SUBCASE("Test adding a player") {
    GameLogic::Ship newPlayer(1, 1, 12, 12, 1, 1);
    gameState.setPlayer(newPlayer);
    auto playerShip2 = gameState.getPlayer();
    CHECK(playerShip2.xPosition == 1);
    CHECK(playerShip2.yPosition == 1);
    CHECK(playerShip2.width == 12);
    CHECK(playerShip2.height == 12);
    CHECK(playerShip2.movementSpeed == 1);
  }
}
TEST_CASE("Test moving ships") {

  SUBCASE("Test moving in the middle") {
    GameLogic::Ship ship1(10, 10, 10, 10, 1, 1);
    int screenWidth = 100;
    int screenHeight = 100;
    GameLogic::moveShip(ship1, GameLogic::MoveDirection::UP, screenWidth,
                        screenHeight);
    CHECK(ship1.xPosition == 10);
    CHECK(ship1.yPosition == 9);
    GameLogic::moveShip(ship1, GameLogic::MoveDirection::RIGHT, screenWidth,
                        screenHeight);
    CHECK(ship1.xPosition == 11);
    CHECK(ship1.yPosition == 9);
    GameLogic::moveShip(ship1, GameLogic::MoveDirection::DOWN, screenWidth,
                        screenHeight);
    CHECK(ship1.xPosition == 11);
    CHECK(ship1.yPosition == 10);
    GameLogic::moveShip(ship1, GameLogic::MoveDirection::LEFT, screenWidth,
                        screenHeight);
    CHECK(ship1.xPosition == 10);
    CHECK(ship1.yPosition == 10);
  }
  SUBCASE("Test moving in the topleft corner") {
    GameLogic::Ship ship1(0, 0, 10, 10, 1, 1);
    int screenWidth = 100;
    int screenHeight = 100;

    SUBCASE("Test moving left") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::LEFT, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 0);
      CHECK(ship1.yPosition == 0);
    }

    SUBCASE("Test moving up") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::UP, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 0);
      CHECK(ship1.yPosition == 0);
    }

    SUBCASE("Test moving right") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::RIGHT, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 1);
      CHECK(ship1.yPosition == 0);
    }

    SUBCASE("Test moving down") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::DOWN, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 0);
      CHECK(ship1.yPosition == 1);
    }
  }

  SUBCASE("Test moving in the bottomright corner") {
    GameLogic::Ship ship1(90, 90, 10, 10, 1, 1);
    int screenWidth = 100;
    int screenHeight = 100;

    SUBCASE("Test moving left") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::LEFT, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 89);
      CHECK(ship1.yPosition == 90);
    }

    SUBCASE("Test moving up") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::UP, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 90);
      CHECK(ship1.yPosition == 89);
    }

    SUBCASE("Test moving right") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::RIGHT, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 90);
      CHECK(ship1.yPosition == 90);
    }

    SUBCASE("Test moving down") {
      GameLogic::moveShip(ship1, GameLogic::MoveDirection::DOWN, screenWidth,
                          screenHeight);
      CHECK(ship1.xPosition == 90);
      CHECK(ship1.yPosition == 90);
    }
  }
}
