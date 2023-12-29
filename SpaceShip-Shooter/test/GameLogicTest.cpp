#include "../src/GameLogic.hpp"
#include "../src/Ship.hpp"
#include "doctest.h"

int factorial(int number) {
  return number > 1 ? factorial(number - 1) * number : 1;
}

TEST_CASE("testing the factorial function") {
  CHECK(factorial(0) == 1);
  CHECK(factorial(1) == 1);
  CHECK(factorial(2) == 2);
  CHECK(factorial(3) == 6);
  CHECK(factorial(10) == 3628800);
}
TEST_CASE("testing functionality ") {
  // TODO
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
    REQUIRE(playerShip2.x_position == 1);
    REQUIRE(playerShip2.y_position == 1);
    REQUIRE(playerShip2.width == 12);
    REQUIRE(playerShip2.height == 12);
    REQUIRE(playerShip2.movementSpeed == 1);
  }
}
