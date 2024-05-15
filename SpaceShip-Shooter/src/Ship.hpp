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
  void setNrOfLives(int nrOfLives) {
    if (nrOfLives >= 0) {
      nrOfLives = nrOfLives;
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
