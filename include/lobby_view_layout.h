#ifndef LOBBY_VIEW_LAYOUT_H
#define LOBBY_VIEW_LAYOUT_H

#include "side.h"
#include "lobby_view_item.h"
#include "screen_rect.h"
#include "layout.h"

#include <vector>

/// The layout of the Lobby dialog.
///
/// ```text
///   x          x x          x x          x x          x
///   1          2 3          4 5          6 7          8
///
/// +-----------------------------------------------------+
/// |                                                     |
/// | +----------+ +-----------------------+ +----------+ | y1
/// | |          | |                       | |          | |
/// | | lhs_     | |                       | | rhs_     | |
/// | | controls | |                       | | controls | |
/// | |          | |        title          | |          | |
/// | |          | |                       | |          | |
/// | |          | |                       | |          | |
/// | |          | |                       | |          | |
/// | |          | +-----------------------+ |          | | y2
/// | |          |                           |          | |
/// | |          | +----------+ +----------+ |          | | y3
/// | |          | |          | |          | |          | |
/// | |          | | color    | | color    | |          | |
/// | |          | |          | |          | |          | |
/// | |          | +----------+ +----------+ |          | | y4
/// | |          |                           |          | |
/// | |          | +----------+ +----------+ |          | | y5
/// | |          | |          | |          | |          | |
/// | |          | | racee    | | race     | |          | |
/// | |          | |          | |          | |          | |
/// | |          | +----------+ +----------+ |          | | y6
/// | |          |                           |          | |
/// | |          | +----------+ +----------+ |          | | y7 <-+
/// | |          | |          | |          | |          | |      |
/// | |          | | ready    | | read     | |          | |      +- panel_height
/// | |          | |          | |          | |          | |      |
/// | +----------+ +----------+ +----------+ +----------+ | y8 <-+
/// |                                                     |
/// +-----------------------------------------------------+
///
///              ^          ^
///              |          |
///              +----------+
///               panel_width
/// ```
class lobby_view_layout
{
public:
  explicit lobby_view_layout(
    const screen_coordinate& window_size = get_default_screen_size(),
    const int margin_width = get_default_margin_width()
  );

  const auto& get_background() const noexcept { return m_background; }
  const screen_rect& get_color(const side player_side) const noexcept;
  const screen_rect& get_controls(const side player_side) const noexcept;
  const screen_rect& get_race(const side player_side) const noexcept;
  const screen_rect& get_start(const side player_side) const noexcept;
  const auto& get_title() const noexcept { return m_title; }

  /// Get the size of the font that would fit nicely
  int get_font_size() const noexcept { return m_font_size; }

  screen_coordinate get_window_size() const noexcept { return m_window_size; }

private:

  screen_rect m_background;
  screen_rect m_lhs_color;
  screen_rect m_lhs_controls;
  screen_rect m_lhs_race;
  screen_rect m_lhs_start;
  screen_rect m_rhs_color;
  screen_rect m_rhs_controls;
  screen_rect m_rhs_race;
  screen_rect m_rhs_start;
  screen_rect m_title;

  lobby_view_item m_lhs_cursor;
  lobby_view_item m_rhs_cursor;

  /// The size of the font that would fit nicely
  int m_font_size;

  /// The size of the window
  screen_coordinate m_window_size;
};

/// Get the rectangle of the item
const screen_rect& get_cursor_rect(
  const lobby_view_layout& layout,
  const lobby_view_item item,
  const side player_side
) noexcept;

/// Get the panels in the layout
std::vector<screen_rect> get_panels(const lobby_view_layout& layout);

/// Test the lobby_view_layout class
void test_lobby_view_layout();

#endif // LOBBY_VIEW_LAYOUT_H
