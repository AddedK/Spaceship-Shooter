#include "../src/game_logic/GameLogic.hpp"
#include "../src/game_logic/Point.hpp"
#include "../src/game_logic/Ship.hpp"
#include "doctest.h"
TEST_CASE("Testing GameState Functionality ") {
  GameLogic::GameState gameState(60, 10, 10);
  REQUIRE(gameState.getEnemyShips().size() == 0);
  auto playerShip = gameState.getPlayer();
  REQUIRE(playerShip.vertices.size() == 0); // Default constructed

  SUBCASE("Test adding a player") {
    std::vector<GameLogic::Point> playerVertices;
    playerVertices.push_back(GameLogic::Point{10, 10});
    playerVertices.push_back(GameLogic::Point{5, 15});
    playerVertices.push_back(GameLogic::Point{15, 15});
    gameState.setPlayer({playerVertices,
                         GameLogic::GameConstants::playerInitialSpeed,
                         GameLogic::GameConstants::playerInitialNrOfLives});
    auto playerShip2 = gameState.getPlayer();
    CHECK(playerShip2.vertices.size() == 3);
    CHECK(playerShip2.lowestX == 5);
    CHECK(playerShip2.lowestY == 10);
    CHECK(playerShip2.highestX == 15);
    CHECK(playerShip2.highestY == 15);
    CHECK(playerShip2.movementSpeed ==
          GameLogic::GameConstants::playerInitialSpeed);
    CHECK(playerShip2.middlePositionX == 10);
  }
}

TEST_CASE("Line intersecting function") {
  SUBCASE("Two parallel lines") {
    GameLogic::Point t1{0, 0};
    GameLogic::Point t2{10, 0};
    GameLogic::Point g1{0, 10};
    GameLogic::Point g2{10, 10};
    CHECK_FALSE(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Two non-intersecting orthogonal lines") {
    GameLogic::Point t1{0, 0};
    GameLogic::Point t2{10, 0};
    GameLogic::Point g1{5, 1};
    GameLogic::Point g2{5, 11};
    CHECK_FALSE(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Non-intersecting angle and straight lines") {
    GameLogic::Point t1{0, 0};
    GameLogic::Point t2{10, 0};
    GameLogic::Point g1{2, 5};
    GameLogic::Point g2{5, 1};
    CHECK_FALSE(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Intersect at corner") {
    GameLogic::Point t1{10, 10};
    GameLogic::Point t2{20, 20};
    GameLogic::Point g1{20, 20};
    GameLogic::Point g2{30, 10};
    CHECK(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Intersect in middle") {
    GameLogic::Point t1{10, 10};
    GameLogic::Point t2{20, 10};
    GameLogic::Point g1{15, 5};
    GameLogic::Point g2{15, 15};
    CHECK(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Intersect cross") {
    GameLogic::Point t1{10, 0};
    GameLogic::Point t2{0, 10};
    GameLogic::Point g1{0, 0};
    GameLogic::Point g2{10, 10};
    CHECK(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Collinear fully overlapping") {
    GameLogic::Point t1{10, 0};
    GameLogic::Point t2{0, 10};
    GameLogic::Point g1{10, 0};
    GameLogic::Point g2{0, 10};
    CHECK(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
  SUBCASE("Collinear partial overlapping") {
    GameLogic::Point t1{10, 0};
    GameLogic::Point t2{0, 10};
    GameLogic::Point g1{10, 0};
    GameLogic::Point g2{5, 5};
    CHECK(GameLogic::lineIsIntersecting(t1, t2, g1, g2));
  }
}
