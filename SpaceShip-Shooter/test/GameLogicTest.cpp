#include "../src/GameLogic.hpp"
#include "../src/Ship.hpp"
#include "doctest.h"

int factorial(int number) {
  return number > 1 ? factorial(number - 1) * number : 1;
}

TEST_CASE("Testing functionality ") {
  GameLogic::GameState gameState(10, 10);
  REQUIRE(gameState.getEnemyShips().size() == 0);
  auto playerShip = gameState.getPlayer();
  REQUIRE(playerShip.x_position == 0);
  REQUIRE(playerShip.y_position == 0);
  REQUIRE(playerShip.width == 10);
  REQUIRE(playerShip.height == 10);
  REQUIRE(playerShip.movementSpeed == 1);

  SUBCASE("Test adding a player") {
    GameLogic::Ship newPlayer(1, 1, 12, 12);
    gameState.setPlayer(newPlayer);
    auto playerShip2 = gameState.getPlayer();
    CHECK(playerShip2.x_position == 1);
    CHECK(playerShip2.y_position == 1);
    CHECK(playerShip2.width == 12);
    CHECK(playerShip2.height == 12);
    CHECK(playerShip2.movementSpeed == 1);
  }
}
