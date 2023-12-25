#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

namespace GameLogic {

enum class KeyPress { LEFT, UP, RIGHT, DOWN, ENTER, Q };

class PlayerState {
  // TODO: Move this to separate file
  int x_position;
  int y_position;

public:
  PlayerState() : x_position(0), y_position(0) {}
  PlayerState(int x_position, int y_position)
      : x_position(x_position), y_position(x_position) {}
  PlayerState(const PlayerState &otherPlayer) = default;
  PlayerState &operator=(const PlayerState &otherPlayer) = delete;

  ~PlayerState() = default;
};

class GameState {
  PlayerState player;

public:
  GameState();
  GameState(PlayerState player) : player(player) {}
  GameState(const GameState &otherGame) = delete;
  GameState &operator=(const GameState &otherGame) = delete;
  ~GameState() = default;
};

} // namespace GameLogic

#endif // GAME_LOGIC_HPP
