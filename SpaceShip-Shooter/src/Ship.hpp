#ifndef SHIP_HPP
#define SHIP_HPP
namespace GameLogic {

class Ship {
public:
  // Top left corner
  int xPosition;
  int yPosition;
  // Size of the player
  int width;
  int height;
  int movementSpeed;

  Ship()
      : xPosition(0), yPosition(0), width(10), height(10), movementSpeed(1) {}
  Ship(int xPosition, int yPosition, int width, int height)
      : xPosition(xPosition), yPosition(yPosition), width(width),
        height(height), movementSpeed(1) {}
  Ship(const Ship &otherPlayer) = default;
  Ship &operator=(const Ship &otherPlayer) = default;
  void setMovementSpeed(int newSpeed) {
    if (newSpeed >= 0) {
      movementSpeed = newSpeed;
    }
  }
  ~Ship() = default;
};
} // namespace GameLogic
#endif
