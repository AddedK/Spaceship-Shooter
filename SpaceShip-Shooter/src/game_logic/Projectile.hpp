#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Point.hpp"
#include "gameEnums.hpp"
#include <vector>
namespace GameLogic {
class Projectile {
public:
  std::vector<Point> vertices;
  int middlePositionX;
  int lowestX;
  int highestX;
  int lowestY;
  int highestY;
  int movementSpeed;
  MoveDirection direction;

  bool isHoming;

  Projectile()
      : vertices(), middlePositionX(0), lowestX(0), highestX(0), lowestY(0),
        highestY(0), movementSpeed(1), direction(MoveDirection::DOWN),
        isHoming(false) {}
  Projectile(std::vector<Point> vertices, int movementSpeed,
             MoveDirection direction, bool isHoming = false)
      : vertices(vertices), movementSpeed(movementSpeed), direction(direction),
        isHoming(isHoming) {

    int sumX = 0;
    for (Point point : vertices) {
      sumX += point.x;
    }
    middlePositionX = sumX / vertices.size();
    lowestX = 99999;
    highestX = 0;
    lowestY = 999999;
    highestY = 0;
    for (int i = 0; i < vertices.size(); ++i) {
      if (vertices[i].y < lowestY) {
        lowestY = vertices[i].y;
      }
      if (vertices[i].y > highestY) {
        highestY = vertices[i].y;
      }
      if (vertices[i].x < lowestX) {
        lowestX = vertices[i].x;
      }
      if (vertices[i].x > highestX) {
        highestX = vertices[i].x;
      }
    }
  }
  Projectile(const Projectile &otherProjectile) = default;
  Projectile &operator=(const Projectile &otherProjectile) = default;
  void setMovementSpeed(int newSpeed) {
    if (newSpeed >= 0) {
      movementSpeed = newSpeed;
    }
  }
  ~Projectile() = default;
};
} // namespace GameLogic
#endif
