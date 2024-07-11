#include "../src/game_logic/GameLogic.hpp"
#include "../src/game_logic/Ship.hpp"
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
TEST_CASE("Test ship + ship collision checking") {
  SUBCASE("Self collision") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    CHECK(isColliding(ship1, ship1));
  }
  SUBCASE("X-Adjacent ships not colliding") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Ship ship2(16, 10, 5, 5, 1, 3);
    CHECK_FALSE(isColliding(ship1, ship2));
  }
  SUBCASE("Y-Adjacent ships not colliding") {
    GameLogic::Ship ship1(10, 16, 5, 5, 1, 3);
    GameLogic::Ship ship2(10, 10, 5, 5, 1, 3);
    CHECK_FALSE(isColliding(ship1, ship2));
  }
  SUBCASE("X-Edge collision") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Ship ship2(15, 10, 5, 5, 1, 3);
    CHECK(isColliding(ship1, ship2));
    CHECK(isColliding(ship2, ship1)); // Check symmetry
  }
  SUBCASE("Y-Edge collision") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Ship ship2(10, 15, 5, 5, 1, 3);
    CHECK(isColliding(ship1, ship2));
    CHECK(isColliding(ship2, ship1)); // Check symmetry
  }
  SUBCASE("Small intersection") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Ship ship2(14, 12, 2, 2, 1, 3);
    CHECK(isColliding(ship1, ship2));
  }
}
TEST_CASE("Test ship + projectile collision checking") {
  SUBCASE("Close but no collision") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Projectile projectile1(16, 10, 3, 3, 1,
                                      GameLogic::MoveDirection::UP);
    CHECK_FALSE(isColliding(ship1, projectile1));
  }
  SUBCASE("Hit from above") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Projectile projectile1(10, 10, 3, 3, 1,
                                      GameLogic::MoveDirection::DOWN);
    CHECK(isColliding(ship1, projectile1));
  }
  SUBCASE("Hit from below") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Projectile projectile1(15, 15, 3, 3, 1,
                                      GameLogic::MoveDirection::UP);
    CHECK(isColliding(ship1, projectile1));
  }
  SUBCASE("Hit from left") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Projectile projectile1(8, 11, 3, 3, 1,
                                      GameLogic::MoveDirection::RIGHT);
    CHECK(isColliding(ship1, projectile1));
  }
  SUBCASE("Hit from right") {
    GameLogic::Ship ship1(10, 10, 5, 5, 1, 3);
    GameLogic::Projectile projectile1(14, 10, 3, 3, 1,
                                      GameLogic::MoveDirection::LEFT);
    CHECK(isColliding(ship1, projectile1));
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
