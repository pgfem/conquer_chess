#include "menu_view_layout.h"

#include <cassert>
#include <cmath>

menu_view_layout::menu_view_layout(
  const screen_coordinate& window_size,
  const int margin_width
) : m_font_size{64},
    m_window_size{window_size}
{
  const int n_vertical_units{10};
  const int n_margins{n_vertical_units + 1}; // margins are above, below and between panels
  const int panel_height{
    static_cast<int>(
      static_cast<double>(
        window_size.get_y() - (n_margins * margin_width))
        / static_cast<double>(n_vertical_units)
    )
  };
  const int panel_width{
    (window_size.get_y() - (2 * margin_width)) / 2
  };
  const int x1{(window_size.get_x() / 2) - (panel_width / 2)};
  const int x2{x1 + panel_width};

  const int y1{margin_width};
  const int y2{y1 + panel_height + margin_width + panel_height};
  const int y3{y2 + margin_width};
  const int y4{y3 + panel_height};
  const int y5{y4 + margin_width};
  const int y6{y5 + panel_height + panel_height + margin_width + panel_height + margin_width};
  const int y7{y6 + margin_width};
  const int y8{y7 + panel_height};
  const int y9{y8 + margin_width};
  const int y10{y9 + panel_height};
  const int y11{y10 + margin_width};
  const int y12{y11 + panel_height};
  const int y13{y12 + margin_width};
  const int y14{y13 + panel_height};

  m_title = screen_rect(
    screen_coordinate(x1, y1),
    screen_coordinate(x2, y2)
  );
  m_subtitle = screen_rect(
    screen_coordinate(x1, y3),
    screen_coordinate(x2, y4)
  );
  m_image = screen_rect(
    screen_coordinate(x1, y5),
    screen_coordinate(x2, y6)
  );
  m_start = screen_rect(
    screen_coordinate(x1, y7),
    screen_coordinate(x2, y8)
  );
  m_options = screen_rect(
    screen_coordinate(x1, y9),
    screen_coordinate(x2, y10)
  );
  m_about = screen_rect(
    screen_coordinate(x1, y11),
    screen_coordinate(x2, y12)
  );
  m_quit = screen_rect(
    screen_coordinate(x1, y13),
    screen_coordinate(x2, y14)
  );

  m_font_size = std::min(
    panel_height / 2,
    panel_width / 6
  );
}

std::vector<screen_rect> get_panels(const menu_view_layout& layout)
{
  return
  {
    layout.get_title(),
    layout.get_subtitle(),
    layout.get_start(),
    layout.get_options(),
    layout.get_about(),
    layout.get_quit()
  };
}


const screen_rect& menu_view_layout::get_selectable_rect(const menu_view_item item) const noexcept
{
  switch (item)
  {
    case menu_view_item::start: return m_start;
    case menu_view_item::options: return m_options;
    case menu_view_item::about: return m_about;
    default:
    case menu_view_item::quit:
      assert(item == menu_view_item::quit);
      return m_quit;
  }
}

void test_menu_view_layout()
{
  #ifndef NDEBUG
  // get_panels
  {
    const menu_view_layout layout;
    assert(!get_panels(layout).empty());
  }
  // get_selectable_rect
  {
    const menu_view_layout layout;
    assert(layout.get_selectable_rect(menu_view_item::start) == layout.get_start());
    assert(layout.get_selectable_rect(menu_view_item::options) == layout.get_options());
    assert(layout.get_selectable_rect(menu_view_item::about) == layout.get_about());
    assert(layout.get_selectable_rect(menu_view_item::quit) == layout.get_quit());
  }
  #endif
}
