#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
namespace GameLogic {

enum class KeyPress { LEFT, UP, RIGHT, DOWN, ENTER, Q };

class PlayerState {
  // TODO: Move this to separate file
public:
  int x_position;
  int y_position;

  PlayerState() : x_position(0), y_position(0) {}
  PlayerState(int x_position, int y_position)
      : x_position(x_position), y_position(x_position) {}
  PlayerState(const PlayerState &otherPlayer) = default;
  PlayerState &operator=(const PlayerState &otherPlayer) = default;

  ~PlayerState() = default;
};

class GameState {
  PlayerState player;

public:
  PlayerState getPlayer() const { return player; }
  void setPlayer(PlayerState player);
  void handleKeyPress(KeyPress keyPress);
  void movePlayer(KeyPress keyPress);

  GameState() = default;
  GameState(PlayerState player) : player(player) {}
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

} // namespace GameLogic

#endif // GAME_LOGIC_HPP
