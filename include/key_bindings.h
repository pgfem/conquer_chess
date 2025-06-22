#ifndef KEY_BINDINGS_H
#define KEY_BINDINGS_H

#include "ccfwd.h"
#include "user_input_type.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <iosfwd>
#include <vector>

/// The key bindings.
///
/// This class connects a key to an action,
/// where an action can be a cursor movement
/// or an actual action, such as attack, move, etc.
class key_bindings
{
public:
  key_bindings(
    const sf::Keyboard::Key up,
    const sf::Keyboard::Key right,
    const sf::Keyboard::Key down,
    const sf::Keyboard::Key left,
    const sf::Keyboard::Key action_1,
    const sf::Keyboard::Key action_2,
    const sf::Keyboard::Key action_3,
    const sf::Keyboard::Key action_4
  );

  /// From an event, create zero or one user inputs.
  /// Return the 'user_input_type' corresponding to an event
  std::vector<user_input_type> create_actions(
    const sf::Keyboard::Key k
  ) const noexcept;

  /// Get the key for action 1, 2, 3 or 4.
  sf::Keyboard::Key get_key_for_action(const action_number& action) const;

  /// Get the key for moving down
  sf::Keyboard::Key get_key_for_move_down() const noexcept { return m_down; }

  /// Get the key for moving left
  sf::Keyboard::Key get_key_for_move_left() const noexcept { return m_left; }

  /// Get the key for moving right
  sf::Keyboard::Key get_key_for_move_right() const noexcept { return m_right;  }

  /// Get the key for moving up
  sf::Keyboard::Key get_key_for_move_up() const noexcept { return m_up; }

private:

  std::vector<sf::Keyboard::Key> m_actions;
  sf::Keyboard::Key m_down;
  sf::Keyboard::Key m_left;
  sf::Keyboard::Key m_right;
  sf::Keyboard::Key m_up;
};

/// Create the key bindings for a player at the left side of a keyboard
key_bindings create_left_keyboard_key_bindings() noexcept;

/// Create the key bindings for a player at the right side of a keyboard
key_bindings create_right_keyboard_key_bindings() noexcept;

/// Get the key for a specific action
sf::Keyboard::Key get_key_for_action(
  const key_bindings& k,
  const action_number& action
) noexcept;

/// Test this class and its free functions
void test_key_bindings();

bool operator==(const key_bindings& lhs, const key_bindings& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const key_bindings& keys) noexcept;

#endif // KEY_BINDINGS_H
