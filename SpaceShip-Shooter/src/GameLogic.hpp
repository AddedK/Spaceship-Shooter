#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
namespace GameLogic {

enum class KeyPress { LEFT, UP, RIGHT, DOWN, ENTER, Q };

class PlayerState {
  // TODO: Move this to separate file
public:
  // Top left corner
  int x_position;
  int y_position;
  // Size of the player
  int width;
  int height;

  PlayerState() : x_position(0), y_position(0), width(10), height(10) {}
  PlayerState(int x_position, int y_position, int width, int height)
      : x_position(x_position), y_position(x_position), width(width),
        height(height) {}
  PlayerState(const PlayerState &otherPlayer) = default;
  PlayerState &operator=(const PlayerState &otherPlayer) = default;

  ~PlayerState() = default;
};

class GameState {
  PlayerState player;
  int screenWidth;
  int screenHeight;

public:
  PlayerState getPlayer() const { return player; }
  void setPlayer(PlayerState player);
  void handleKeyPress(KeyPress keyPress);
  void movePlayer(KeyPress keyPress);
  void setDimensions(int screenWidth, int screenHeight);

  // TODO: Make sanity checks on how people construct GameState
  GameState() = delete;
  GameState(int screenWidth, int screenHeight)
      : screenWidth(screenWidth), screenHeight(screenHeight) {}
  // PlayerState default constructed
  GameState(PlayerState player, int screenWidth, int screenHeight)
      : player(player), screenWidth(screenWidth), screenHeight(screenHeight) {}
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

} // namespace GameLogic

#endif // GAME_LOGIC_HPP
