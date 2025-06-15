#include "controls_view.h"

#ifndef LOGIC_ONLY

#include "screen_coordinate.h"
#include "physical_controllers.h"
#include "render_window.h"
#include "action_number.h"
#include "sfml_helper.h"
#include <cassert>
#include <cmath>
#include <iostream>

controls_view::controls_view(const side& player_side)
  : m_player_side(player_side),
    m_selected{controls_view_item::type}
{

}
void controls_view::change_selected()
{

  switch (m_selected)
  {
    case controls_view_item::type:
      physical_controllers::get().get_controller(m_player_side).set_type(
        get_next(physical_controllers::get().get_controller(m_player_side).get_type())
      );
    break;
    default:
      std::clog << "TODO\n";
  }
}

void draw_panel(
  controls_view& v,
  const screen_rect& panel_position,
  const std::string panel_text,
  const chess_color color,
  const bool is_active
)
{
  sf::RectangleShape rectangle;
  set_rect(rectangle, panel_position);
  rectangle.setTexture(
    &get_strip(color)
  );
  if (!is_active) rectangle.setFillColor(sf::Color(128, 128, 128, 128));
  get_render_window().draw(rectangle);

  sf::Text text;
  v.set_text_style(text);
  text.setString(panel_text);
  set_text_position(text, panel_position);
  get_render_window().draw(text);
}

void controls_view::tick()
{
}

std::string get_key_str_for_action_1(const controls_view& v)
{
  return to_str(
    physical_controllers::get().get_controller(v.get_player_side())
      .get_key_bindings().get_key_for_action(action_number(1))
    );
}

std::string get_key_str_for_action_2(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_action(action_number(2)));
}

std::string get_key_str_for_action_3(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_action(action_number(3)));
}

std::string get_key_str_for_action_4(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_action(action_number(4)));
}

std::string get_key_str_for_do(const controls_view& /* v */)
{
  return "LMB";
}

std::string get_key_str_for_move_down(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_move_down());
}

std::string get_key_str_for_move_left(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_move_left());
}
std::string get_key_str_for_move_right(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_move_right());
}
std::string get_key_str_for_move_up(const controls_view& v)
{
  return to_str(physical_controllers::get().get_controller(v.get_player_side()).get_key_bindings().get_key_for_move_up());
}

std::string get_key_str_for_next(const controls_view& /* v */)
{
  return "RMB";
}

bool controls_view::process_event(sf::Event& event)
{
  if (event.type == sf::Event::Closed)
  {
    m_next_state = program_state::options;
    return false;
  }
  else if (event.type == sf::Event::KeyPressed)
  {
    sf::Keyboard::Key key_pressed = event.key.code;
    if (key_pressed == sf::Keyboard::Key::Escape)
    {
      m_next_state = program_state::options;
      return false;
    }
    else if (key_pressed == sf::Keyboard::Key::Up)
    {
      m_selected = get_previous(m_selected);
      game_resources::get().get_sound_effects().play_hide();
    }
    else if (key_pressed == sf::Keyboard::Key::Right)
    {
      m_selected = get_next(m_selected);
      game_resources::get().get_sound_effects().play_hide();
    }
    else if (key_pressed == sf::Keyboard::Key::Down)
    {
      m_selected = get_next(m_selected);
      game_resources::get().get_sound_effects().play_hide();
    }
    else if (key_pressed == sf::Keyboard::Key::Left)
    {
      m_selected = get_previous(m_selected);
      game_resources::get().get_sound_effects().play_hide();
    }
    else if (key_pressed == sf::Keyboard::Key::Space)
    {
      change_selected();
    }
    else if (key_pressed == sf::Keyboard::Key::Q)
    {
      m_next_state = program_state::options;
      return false;
    }
  }
  else if (event.type == sf::Event::MouseMoved)
  {
    const auto mouse_screen_pos{
      screen_coordinate(event.mouseMove.x, event.mouseMove.y)
    };
    if (is_in(mouse_screen_pos, m_layout.get_action_1_value())) m_selected = controls_view_item::action_1;
    if (is_in(mouse_screen_pos, m_layout.get_action_2_value())) m_selected = controls_view_item::action_2;
    if (is_in(mouse_screen_pos, m_layout.get_action_3_value())) m_selected = controls_view_item::action_3;
    if (is_in(mouse_screen_pos, m_layout.get_action_4_value())) m_selected = controls_view_item::action_4;
    if (is_in(mouse_screen_pos, m_layout.get_controller_type_value())) m_selected = controls_view_item::type;
    if (is_in(mouse_screen_pos, m_layout.get_do_value())) m_selected = controls_view_item::do_action;
    if (is_in(mouse_screen_pos, m_layout.get_down_value())) m_selected = controls_view_item::down;
    if (is_in(mouse_screen_pos, m_layout.get_left_value())) m_selected = controls_view_item::left;
    if (is_in(mouse_screen_pos, m_layout.get_next_value())) m_selected = controls_view_item::next_action;
    if (is_in(mouse_screen_pos, m_layout.get_right_value())) m_selected = controls_view_item::right;
    if (is_in(mouse_screen_pos, m_layout.get_up_value())) m_selected = controls_view_item::up;
  }
  else if (event.type == sf::Event::MouseButtonPressed)
  {
    change_selected();
  }
  return false; // Do not close the window :-)
}

void controls_view::process_resize_event(sf::Event& event)
{
  assert(event.type == sf::Event::Resized);

  // From https://www.sfml-dev.org/tutorials/2.2/graphics-view.php#showing-more-when-the-window-is-resized
  const sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
  get_render_window().setView(sf::View(visible_area));
  m_layout = controls_view_layout(
    screen_coordinate(event.size.width, event.size.height),
    get_default_margin_width()
  );
}

void controls_view::set_text_style(sf::Text& text)
{
  text.setFont(get_arial_font());
  text.setStyle(sf::Text::Bold);
  text.setCharacterSize(32);
  text.setFillColor(sf::Color::Black);
}
void controls_view::draw()
{
  show_layout_panels(*this);

  show_type_panel(*this);
  show_keyboard_panel(*this);
  show_mouse_panel(*this);
  show_selected_panel(*this);
}

void show_keyboard_panel(controls_view& v)
{
  const auto& layout = v.get_layout();
  std::vector<std::pair<screen_rect, std::string>> labels =
  {
    std::make_pair(layout.get_up_label(), "Up"),
    std::make_pair(layout.get_right_label(), "Right"),
    std::make_pair(layout.get_down_label(), "Down"),
    std::make_pair(layout.get_left_label(), "Left"),
    std::make_pair(layout.get_action_1_label(), "1"),
    std::make_pair(layout.get_action_2_label(), "2"),
    std::make_pair(layout.get_action_3_label(), "3"),
    std::make_pair(layout.get_action_4_label(), "4")
  };
  const bool is_active{
    physical_controllers::get().get_controller(v.get_player_side()).get_type() == physical_controller_type::keyboard
  };
  chess_color color{chess_color::black};
  for (const auto& p: labels)
  {
    draw_panel(v, p.first, p.second, color, is_active);
    color = get_other_color(color);
  }

  std::vector<std::pair<screen_rect, std::string>> values =
  {
    std::make_pair(layout.get_up_value(), get_key_str_for_move_up(v)),
    std::make_pair(layout.get_right_value(), get_key_str_for_move_right(v)),
    std::make_pair(layout.get_down_value(), get_key_str_for_move_down(v)),
    std::make_pair(layout.get_left_value(), get_key_str_for_move_left(v)),
    std::make_pair(layout.get_action_1_value(), get_key_str_for_action_1(v)),
    std::make_pair(layout.get_action_2_value(), get_key_str_for_action_2(v)),
    std::make_pair(layout.get_action_3_value(), get_key_str_for_action_3(v)),
    std::make_pair(layout.get_action_4_value(), get_key_str_for_action_4(v))
  };
  color = get_other_color(color);
  for (const auto& p: values)
  {
    draw_panel(v, p.first, p.second, color, is_active);
    color = get_other_color(color);
  }
}

void show_mouse_panel(controls_view& v)
{
  const auto& layout = v.get_layout();
  std::vector<std::pair<screen_rect, std::string>> labels =
  {
    std::make_pair(layout.get_do_label(), "do"),
    std::make_pair(layout.get_next_label(), "next")
  };
  const bool is_active{
    physical_controllers::get().get_controller(v.get_player_side()).get_type() == physical_controller_type::mouse
  };
  chess_color color{chess_color::black};
  for (const auto& p: labels)
  {
    draw_panel(v, p.first, p.second, color, is_active);
    color = get_other_color(color);
  }

  std::vector<std::pair<screen_rect, std::string>> values =
  {
    std::make_pair(layout.get_do_value(), get_key_str_for_do(v)),
    std::make_pair(layout.get_next_value(), get_key_str_for_next(v)),
  };
  color = get_other_color(color);
  for (const auto& p: values)
  {
    draw_panel(v, p.first, p.second, color, is_active);
    color = get_other_color(color);
  }
}

void show_layout_panels(controls_view& v)
{
  for (const auto& screen_rect: get_panels(v.get_layout()))
  {
    sf::RectangleShape rectangle;
    set_rect(rectangle, screen_rect);
    rectangle.setFillColor(sf::Color(32, 32, 32));
    get_render_window().draw(rectangle);
  }
}

void show_selected_panel(controls_view& v)
{
  const auto select_rect{
    v.get_layout().get_selectable_rect(
      v.get_selected()
    )
  };
  sf::RectangleShape rectangle;
  set_rect(rectangle, select_rect);
  rectangle.setOrigin(
    get_width(select_rect) / 2,
    get_height(select_rect) / 2
  );
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(sf::Color::Red);
  rectangle.setOutlineThickness(5);
  get_render_window().draw(rectangle);
}

void show_type_panel(controls_view& v)
{
  const bool is_active{true};
  draw_panel(
    v,
    v.get_layout().get_controller_type_label(),
    "Controller",
    chess_color::white,
    is_active
  );
  draw_panel(
    v,
    v.get_layout().get_controller_type_value(),
    to_str(physical_controllers::get().get_controller(v.get_player_side()).get_type()),
    chess_color::black,
    is_active
  );
}

void controls_view::start()
{


}

void controls_view::stop()
{


}


#endif // LOGIC_ONLY
