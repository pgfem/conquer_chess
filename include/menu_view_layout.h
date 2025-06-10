#ifndef MENU_VIEW_LAYOUT_H
#define MENU_VIEW_LAYOUT_H

#include "menu_view_item.h"
#include "screen_rect.h"
#include "layout.h"

#include <vector>

/// The layout of the Menu dialog
///
/// ```text
/// Margins      _            _ _                    _
/// ............0 x          x x x                  x width
/// ............  1          2 3 4                  5
/// ............
/// ............+--------------+----------------------+
/// ............|              |                      |
/// ............| +----------+ | +------------------+ |y1
/// ............| |          | | |                  | |
/// ............| | title    | | |                  | |
/// ............| |          | | |                  | |
/// ............| +----------+ | |                  | | y2
/// ............|              | |                  | |
/// ............| +----------+ | |                  | | y3
/// ............| | subtitle | | |                  | |
/// ............| +----------+ | |                  | | y4
/// ............|              | |                  | |
/// ............| +----------+ | |                  | | y5
/// ............| |          | | |                  | |
/// ............| |          | | |                  | |
/// ............| | unused   | | | image            | |
/// ............| |          | | |                  | |
/// ............| |          | | |                  | |
/// ............| +----------+ | |                  | | y6
/// ............|              | |                  | |
/// ............| +----------+ | |                  | | y7
/// ............| | start    | | |                  | |
/// ............| +----------+ | |                  | | y8
/// ............|              | |                  | |
/// ............| +----------+ | |                  | | y9
/// ............| | options  | | |                  | |
/// ............| +----------+ | |                  | | y10
/// ............|              | |                  | |
/// ............| +----------+ | |                  | | y11
/// ............| | about    | | |                  | |
/// ............| +----------+ | |                  | | y12
/// ............|              | |                  | |
/// ............| +----------+ | |                  | | y13
/// ............| | quit     | | |                  | |
/// ............| +----------+ | +------------------+ | y14
/// ............|              |                      |
/// ............+--------------+----------------------+
/// ............
/// ............  ^          ^
/// ............  |          |
/// ............  +----------+
/// ............   panel_width
/// ```
class menu_view_layout
{
public:
  explicit menu_view_layout(
    const screen_coordinate& window_size = get_default_screen_size(),
    const int margin_width = get_default_margin_width()
  );

  /// Get a screen rect
  const screen_rect& get_selectable_rect(const menu_view_item item) const noexcept;

  const auto& get_title() const noexcept { return m_title; }
  const auto& get_subtitle() const noexcept { return m_subtitle; }
  const auto& get_image() const noexcept { return m_image; }
  const auto& get_start() const noexcept { return m_start; }
  const auto& get_about() const noexcept { return m_about; }
  const auto& get_options() const noexcept { return m_options; }
  const auto& get_quit() const noexcept { return m_quit; }

  /// Get the size of the font that would fit nicely
  int get_font_size() const noexcept { return m_font_size; }

  screen_coordinate get_window_size() const noexcept { return m_window_size; }


private:

  screen_rect m_title;
  screen_rect m_subtitle;
  screen_rect m_image;
  screen_rect m_start;
  screen_rect m_options;
  screen_rect m_about;
  screen_rect m_quit;

  /// The size of the font that would fit nicely
  int m_font_size;

  /// The size of the window
  screen_coordinate m_window_size;
};

/// Get the panels in the layout
std::vector<screen_rect> get_panels(const menu_view_layout& layout);

/// Test the menu_view_layout class
void test_menu_view_layout();

#endif // MENU_VIEW_LAYOUT_H
