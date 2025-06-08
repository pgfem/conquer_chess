#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "ccfwd.h"

#include "user_input_type.h"
#include "game_coordinate.h"
#include "side.h"

#include <iosfwd>
#include <random>
#include <optional>
#include <SFML/Window/Event.hpp>

/// A user input.
class user_input
{
public:
  explicit user_input(
    const user_input_type type,
    const side player,
    const std::optional<game_coordinate>& coordinat = {}
  );
  auto get_user_input_type() const noexcept { return m_user_input_type; }
  auto& get_coordinat() const noexcept { return m_coordinat; }
  auto get_player() const noexcept { return m_player; }

private:

  user_input_type m_user_input_type;

  /// For the user input types that need a coordinat.
  /// The others need the cursor's current square
  ///
  /// Type           | Does have a coordinat
  /// ---------------|----------------------
  /// press_action_1 | no
  /// press_action_2 | no
  /// press_action_3 | no
  /// press_action_4 | no
  /// press_down     | no
  /// press_left     | no
  /// press_right    | no
  /// press_up       | no
  /// lmb_down       | no
  /// rmb_down       | no
  /// mouse_move     | yes
  ///
  /// @see use \link{does_input_type_need_coordinat} to determine
  /// if the user_input_type needs a coordinat
  std::optional<game_coordinate> m_coordinat;

  side m_player;
};

/// The only `user_input` with a coordinat
user_input create_mouse_move_action(
  const game_coordinate& coordinat,
  const side player
);

/// Do action 1 with keyboard on the square where the player's
/// cursor is.
/// @see Use \link{move_cursor_to} to put the cursor
/// at the square to act upon
user_input create_press_action_1(const side player);

user_input create_press_action_2(const side player);
user_input create_press_action_3(const side player);
user_input create_press_action_4(const side player);
user_input create_press_down_action(const side player);
user_input create_press_left_action(const side player);

/// Do LMB action on the square where the player's
/// cursor is.
/// @see Use \link{move_cursor_to} to put the cursor
/// at the square to act upon
user_input create_press_lmb_action(const side player);

user_input create_press_right_action(const side player);

user_input create_press_rmb_action(const side player);

user_input create_press_up_action(const side player);

user_input create_random_user_input(
  std::default_random_engine& rng_engine
);
/*
/// Get the key for action 1, 2, 3 or 4 for a player
sf::Keyboard::Key get_key_for_action(
  const game& g,
  const side player,
  const action_number& action
);
*/
/// Test the 'control_action' class and its free functions
void test_user_input();

bool operator==(const user_input& lhs, const user_input& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const user_input& a) noexcept;

#endif // USER_INPUT_H

