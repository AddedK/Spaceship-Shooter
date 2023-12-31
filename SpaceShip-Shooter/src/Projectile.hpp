#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "gameEnums.hpp"
namespace GameLogic {
class Projectile {
public:
  int xPosition;
  int yPosition;
  int width;
  int height;
  int movementSpeed;
  MoveDirection direction;

  Projectile()
      : xPosition(0), yPosition(0), width(1), height(1), movementSpeed(1),
        direction(MoveDirection::DOWN) {}
  Projectile(int xPosition, int yPosition, int width, int height,
             int movementSpeed, MoveDirection direction)
      : xPosition(xPosition), yPosition(yPosition), width(width),
        height(height), movementSpeed(movementSpeed), direction(direction) {}
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
