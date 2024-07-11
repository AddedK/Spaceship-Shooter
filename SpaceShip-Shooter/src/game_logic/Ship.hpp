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
  // Edge vertices for this ship. The edges form a closed shape. Two adjacent
  // elements form an edge, including the first and last element.
  std::vector<Point> vertices;
  int movementSpeed;
  int frameWhenLastFiredProjectile;

  Ship()
      : vertices(), movementSpeed(1), nrOfLives(1),
        frameWhenLastFiredProjectile(0) {}
  Ship(std::vector<Point> vertices, int width, int height, int movementSpeed,
       int nrOfLives)
      : vertices(vertices), movementSpeed(movementSpeed), nrOfLives(nrOfLives),
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
