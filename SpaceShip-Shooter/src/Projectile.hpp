#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "gameEnums.hpp"
namespace GameLogic {
class Projectile {
public:
  int x_position;
  int y_position;
  int width;
  int height;
  int movementSpeed;
  MoveDirection direction;

  Projectile()
      : x_position(0), y_position(0), width(1), height(1), movementSpeed(1),
        direction(MoveDirection::DOWN) {}
  Projectile(int x_position, int y_position, int width, int height,
             int movementSpeed, MoveDirection direction)
      : x_position(x_position), y_position(y_position), width(width),
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
