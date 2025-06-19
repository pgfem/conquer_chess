#include "controls_view_layout.h"

#include <cassert>
#include <cmath>

controls_view_layout::controls_view_layout(
  const screen_coordinate& window_size,
  const int margin_width
) : m_window_size{window_size}
{
  const int panel_height{80};
  const int text_panel_width{200};
  const int symbol_panel_width{panel_height};

  const int x1{128 + margin_width};
  const int x2{x1 + text_panel_width};
  const int x3{x2 + symbol_panel_width};
  const int x4{x3 + margin_width};
  const int x5{x4 + text_panel_width};
  const int x6{x5 + symbol_panel_width};

  const int y1{128 + margin_width};
  const int y2{y1 + panel_height};
  const int y3{y2 + margin_width};
  const int y4{y3 + panel_height};
  const int y5{y4 + panel_height};
  const int y6{y5 + panel_height};
  const int y7{y6 + panel_height};
  const int y8{y7 + panel_height};
  const int y9{y8 + panel_height};
  const int y10{y9 + panel_height};
  const int y11{y10 + panel_height};

  m_controller_type_label = screen_rect(
    screen_coordinate(x1, y1),
    screen_coordinate(x2, y2)
  );
  m_controller_type_value = screen_rect(
    screen_coordinate(x2, y1),
    screen_coordinate(x3, y2)
  );


  m_up_label = screen_rect(
    screen_coordinate(x1, y3),
    screen_coordinate(x2, y4)
  );
  m_up_value = screen_rect(
    screen_coordinate(x2, y3),
    screen_coordinate(x3, y4)
  );
  m_right_label = screen_rect(
    screen_coordinate(x1, y4),
    screen_coordinate(x2, y5)
  );
  m_right_value = screen_rect(
    screen_coordinate(x2, y4),
    screen_coordinate(x3, y5)
  );
  m_down_label = screen_rect(
    screen_coordinate(x1, y5),
    screen_coordinate(x2, y6)
  );
  m_down_value = screen_rect(
    screen_coordinate(x2, y5),
    screen_coordinate(x3, y6)
  );
  m_left_label = screen_rect(
    screen_coordinate(x1, y6),
    screen_coordinate(x2, y7)
  );
  m_left_value = screen_rect(
    screen_coordinate(x2, y6),
    screen_coordinate(x3, y7)
  );
  m_action_1_label = screen_rect(
    screen_coordinate(x1, y7),
    screen_coordinate(x2, y8)
  );
  m_action_1_value = screen_rect(
    screen_coordinate(x2, y7),
    screen_coordinate(x3, y8)
  );
  m_action_2_label = screen_rect(
    screen_coordinate(x1, y8),
    screen_coordinate(x2, y9)
  );
  m_action_2_value = screen_rect(
    screen_coordinate(x2, y8),
    screen_coordinate(x3, y9)
  );
  m_action_3_label = screen_rect(
    screen_coordinate(x1, y9),
    screen_coordinate(x2, y10)
  );
  m_action_3_value = screen_rect(
    screen_coordinate(x2, y9),
    screen_coordinate(x3, y10)
  );
  m_action_4_label = screen_rect(
    screen_coordinate(x1, y10),
    screen_coordinate(x2, y11)
  );
  m_action_4_value = screen_rect(
    screen_coordinate(x2, y10),
    screen_coordinate(x3, y11)
  );


  m_do_label = screen_rect(
    screen_coordinate(x4, y3),
    screen_coordinate(x5, y4)
  );
  m_do_value = screen_rect(
    screen_coordinate(x5, y3),
    screen_coordinate(x6, y4)
  );
  m_next_label = screen_rect(
    screen_coordinate(x4, y4),
    screen_coordinate(x5, y5)
  );
  m_next_value = screen_rect(
    screen_coordinate(x5, y4),
    screen_coordinate(x6, y5)
  );
}

std::vector<screen_rect> get_panels(const controls_view_layout& layout)
{
  return
  {
    layout.get_action_1_label(),
    layout.get_action_1_value(),
    layout.get_action_2_label(),
    layout.get_action_2_value(),
    layout.get_action_3_label(),
    layout.get_action_3_value(),
    layout.get_action_4_label(),
    layout.get_action_4_value(),
    layout.get_controller_type_label(),
    layout.get_controller_type_value(),
    layout.get_do_label(),
    layout.get_do_value(),
    layout.get_down_label(),
    layout.get_down_value(),
    layout.get_left_label(),
    layout.get_left_value(),
    layout.get_next_label(),
    layout.get_next_value(),
    layout.get_right_label(),
    layout.get_right_value(),
    layout.get_up_label(),
    layout.get_up_value()
  };
}


const screen_rect& controls_view_layout::get_selectable_rect(const controls_view_item item) const noexcept
{
  switch (item)
  {
    case controls_view_item::type: return m_controller_type_value;
    case controls_view_item::up: return m_up_value;
    case controls_view_item::right: return m_right_value;
    case controls_view_item::down: return m_down_value;
    case controls_view_item::left: return m_left_value;
    case controls_view_item::action_1: return m_action_1_value;
    case controls_view_item::action_2: return m_action_2_value;
    case controls_view_item::action_3: return m_action_3_value;
    case controls_view_item::action_4: return m_action_4_value;
    case controls_view_item::do_action: return m_do_value;
    default:
    case controls_view_item::next_action:
      assert(item == controls_view_item::next_action);
      return m_next_value;
  }
}

void test_controls_view_layout()
{
  #ifndef NDEBUG
  // get_panels
  {
    const controls_view_layout layout;
    assert(!get_panels(layout).empty());

  }
  // get_selectable_rect
  {
    const controls_view_layout layout;
    assert(get_width(layout.get_selectable_rect(controls_view_item::type)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::up)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::right)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::down)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::left)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::action_1)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::action_2)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::action_3)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::action_4)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::do_action)) > 0);
    assert(get_width(layout.get_selectable_rect(controls_view_item::next_action)) > 0);
  }
  #endif
}
