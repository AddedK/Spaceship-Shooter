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
  int middlePositionX;
  int lowestX;
  int highestX;
  int lowestY;
  int highestY;

  int movementSpeed;
  int frameWhenLastFiredProjectile;

  Ship()
      : vertices(), middlePositionX(0), lowestX(0), highestX(0), lowestY(0),
        highestY(0), movementSpeed(1), nrOfLives(1),
        frameWhenLastFiredProjectile(0) {}
  Ship(std::vector<Point> vertices, int width, int height, int movementSpeed,
       int nrOfLives)
      : vertices(vertices), movementSpeed(movementSpeed), nrOfLives(nrOfLives),
        frameWhenLastFiredProjectile(0) {
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
