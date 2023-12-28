#ifndef SHIP_HPP
#define SHIP_HPP
class Ship {
public:
  // Top left corner
  int x_position;
  int y_position;
  // Size of the player
  int width;
  int height;
  int movementSpeed;

  Ship()
      : x_position(0), y_position(0), width(10), height(10), movementSpeed(1) {}
  Ship(int x_position, int y_position, int width, int height)
      : x_position(x_position), y_position(y_position), width(width),
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
#endif
