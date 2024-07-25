#ifndef UPGRADE_HPP
#define UPGRADE_HPP
#include "Point.hpp"
#include "gameEnums.hpp"

namespace GameLogic {
enum class UpgradeType { MOVEMENTSPEED, BONUSLIFE, PROJECTILESPEED };
class Upgrade {
public:
  Point center;
  int radius;
  int movementSpeed;
  MoveDirection direction;
  UpgradeType upgradeType;

  Upgrade() = delete;
  Upgrade(Point center, int radius, int movementSpeed, MoveDirection direction,
          UpgradeType upgradeType)
      : center(center), radius(radius), movementSpeed(movementSpeed),
        direction(direction), upgradeType(upgradeType) {}
  Upgrade &operator=(const Upgrade &otherupgrade) = default;
  ~Upgrade() = default;

  void setMovementSpeed(int newSpeed) {
    if (newSpeed >= 0) {
      movementSpeed = newSpeed;
    }
  }
};
} // namespace GameLogic

#endif
