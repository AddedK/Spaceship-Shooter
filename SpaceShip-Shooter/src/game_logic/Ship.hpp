#ifndef SHIP_HPP
#define SHIP_HPP
#include <vector>

namespace GameLogic {

struct Point {
  int x;
  int y;
};

class Ship {
public:
  std::vector<Point> vertices;
  // Top left corner
  int xPosition;
  int yPosition;
  // Size of the player
  int width;
  int height;
  int movementSpeed;
  int frameWhenLastFiredProjectile;

  Ship()
      : xPosition(0), yPosition(0), width(10), height(10), movementSpeed(1),
        nrOfLives(1), frameWhenLastFiredProjectile(0) {}
  Ship(int xPosition, int yPosition, int width, int height, int movementSpeed,
       int nrOfLives)
      : xPosition(xPosition), yPosition(yPosition), width(width),
        height(height), movementSpeed(movementSpeed), nrOfLives(nrOfLives),
        frameWhenLastFiredProjectile(0) {}
  Ship(const Ship &otherPlayer) = default;
  Ship &operator=(const Ship &otherPlayer) = default;
  void setMovementSpeed(int newSpeed) {
    if (newSpeed >= 0) {
      movementSpeed = newSpeed;
    }
  }
  void decrementNrOfLives(int amount) { nrOfLives -= amount; }
  int getNrOfLives() const { return nrOfLives; }
  ~Ship() = default;

private:
  int nrOfLives;
};

} // namespace GameLogic
#endif
