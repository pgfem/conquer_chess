#include "options_view.h"

#ifndef LOGIC_ONLY

#include "draw.h"
#include "physical_controller.h"
#include "physical_controllers.h"
#include "physical_controller_type.h"
#include "options_view.h"
#include "physical_controllers.h"
#include "game_resources.h"
#include "screen_coordinate.h"
#include "game_options.h"
#include "pieces.h"
#include "physical_controllers.h"
#include "sfml_helper.h"
#include "options_view.h"
#include "render_window.h"

#include <cassert>
#include <sstream>

options_view::options_view()
  : m_selected{options_view_item::game_speed}
{

}

void options_view::decrease_selected()
{
  switch (m_selected)
  {
    case options_view_item::game_speed:
      game_options::get().set_game_speed(get_previous(game_options::get().get_game_speed()));
    break;
    case options_view_item::music_volume:
      game_options::get().set_volume(get_previous(game_options::get().get_music_volume()));
    break;
    case options_view_item::sound_effects_volume:
      game_options::get().set_sound_effects_volume(get_previous(game_options::get().get_sound_effects_volume()));
    break;
    case options_view_item::starting_position:
      assert(!to_str(get_starting_position()).empty());
      game_options::get().set_starting_position(get_previous(get_starting_position()));
      assert(!to_str(get_starting_position()).empty());
    break;
    case options_view_item::left_controls:
    {
      m_next_state = program_state::left_controls;
    }
    break;
    case options_view_item::right_controls:
    {
      m_next_state = program_state::right_controls;
    }
    break;
  }
  game_resources::get().get_sound_effects().play_hide();
}

void options_view::increase_selected()
{
  switch (m_selected)
  {
    case options_view_item::game_speed:
      game_options::get().set_game_speed(get_next(game_options::get().get_game_speed()));
    break;
    case options_view_item::music_volume:
      game_options::get().set_volume(get_next(game_options::get().get_music_volume()));
    break;
    case options_view_item::sound_effects_volume:
      game_options::get().set_sound_effects_volume(get_next(game_options::get().get_sound_effects_volume()));
    break;
    case options_view_item::starting_position:
      assert(!to_str(get_starting_position()).empty());
      game_options::get().set_starting_position(get_next(get_starting_position()));
      assert(!to_str(get_starting_position()).empty());
    break;
    case options_view_item::left_controls:
    {
      m_next_state = program_state::left_controls;
    }
    break;
    case options_view_item::right_controls:
    {
      m_next_state = program_state::right_controls;
    }
    break;
  }
  game_resources::get().get_sound_effects().play_hide();
}

void draw_panel(
  options_view& ,
  const screen_rect& panel_position,
  const std::string panel_text,
  const chess_color color
)
{
  draw_texture(
    get_strip_texture(color),
    panel_position
  );
  /*
  sf::RectangleShape rectangle;
  set_rect(rectangle, panel_position);
  rectangle.setTexture(
    &get_strip_texture(color)
  );
  get_render_window().draw(rectangle);
  */
  draw_normal_text(panel_text, panel_position);
  /*
  sf::Text text;
  v.set_text_style(text);
  text.setString(panel_text);
  set_text_position(text, panel_position);
  get_render_window().draw(text);
  */
}

physical_controller_type get_physical_controller_type(
  const side player)
{
  return physical_controllers::get().get_controller(player).get_type();
}

//starting_position_type get_starting_position(const options_view&) noexcept
//{
//  return get_starting_position();
//}

bool options_view::process_event(sf::Event& event)
{
  if (event.type == sf::Event::Closed)
  {
    m_next_state = program_state::main_menu;
    return false;
  }
  else if (event.type == sf::Event::KeyPressed)
  {
    sf::Keyboard::Key key_pressed = event.key.code;
    if (key_pressed == sf::Keyboard::Key::Escape)
    {
      m_next_state = program_state::main_menu;
      return false;
    }
    if (key_pressed == sf::Keyboard::Key::Q)
    {
      m_next_state = program_state::main_menu;
      return false;
    }
    else if (key_pressed == sf::Keyboard::Key::Up)
    {
      set_selected(get_above(m_selected));
    }
    else if (key_pressed == sf::Keyboard::Key::Right)
    {
      switch (m_selected)
      {
        case options_view_item::game_speed:
        default:
        assert(m_selected == options_view_item::game_speed);
        case options_view_item::music_volume:
        case options_view_item::sound_effects_volume:
        case options_view_item::starting_position:
          increase_selected();
        break;
        case options_view_item::left_controls:
        case options_view_item::right_controls:
          set_selected(get_right_of(m_selected));
        break;
      }
    }
    else if (key_pressed == sf::Keyboard::Key::Down)
    {
      set_selected(get_below(m_selected));
    }
    else if (key_pressed == sf::Keyboard::Key::Left)
    {
      switch (m_selected)
      {
        case options_view_item::game_speed:
        default:
        assert(m_selected == options_view_item::game_speed);
        case options_view_item::music_volume:
        case options_view_item::sound_effects_volume:
        case options_view_item::starting_position:
          decrease_selected();
        break;
        case options_view_item::left_controls:
        case options_view_item::right_controls:
          set_selected(get_left_of(m_selected));
        break;
      }
    }
    else if (key_pressed == sf::Keyboard::Key::Space)
    {
      increase_selected();
    }
  }
  else if (event.type == sf::Event::MouseMoved)
  {
    const auto mouse_screen_pos{
      screen_coordinate(event.mouseMove.x, event.mouseMove.y)
    };
    if (is_in(mouse_screen_pos, m_layout.get_chess_board())) set_selected(options_view_item::starting_position);
    else if (is_in(mouse_screen_pos, m_layout.get_game_speed_value())) set_selected(options_view_item::game_speed);
    else if (is_in(mouse_screen_pos, m_layout.get_controller_type_value(side::lhs))) set_selected(options_view_item::left_controls);
    else if (is_in(mouse_screen_pos, m_layout.get_music_volume_value())) set_selected(options_view_item::music_volume);
    else if (is_in(mouse_screen_pos, m_layout.get_controller_type_value(side::rhs))) set_selected(options_view_item::right_controls);
    else if (is_in(mouse_screen_pos, m_layout.get_sound_effects_volume_value())) set_selected(options_view_item::sound_effects_volume);
    else if (is_in(mouse_screen_pos, m_layout.get_starting_pos_value())) set_selected(options_view_item::starting_position);
  }
  else if (event.type == sf::Event::MouseButtonPressed)
  {
    increase_selected();
  }
  return false; // if no events proceed with tick
}


void options_view::process_resize_event(sf::Event& event)
{
  assert(event.type == sf::Event::Resized);
  // From https://www.sfml-dev.org/tutorials/2.2/graphics-view.php#showing-more-when-the-window-is-resized
  const sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
  get_render_window().setView(sf::View(visibleArea));
  m_layout = options_view_layout(
    screen_coordinate(visibleArea.width, visibleArea.height),
    get_default_margin_width()
  );
}
void options_view::set_selected(const options_view_item i)
{
  if (m_selected != i)
  {
    game_resources::get().get_sound_effects().play_hide();
  }
  m_selected = i;
}

void options_view::set_text_style(sf::Text& text)
{
  text.setFont(get_arial_font());
  text.setStyle(sf::Text::Bold);
  text.setCharacterSize(24);
  text.setCharacterSize(m_layout.get_font_size());
  text.setFillColor(sf::Color::Black);
}

void options_view::draw()
{
  show_layout_panels(*this);

  assert(!to_str(get_starting_position()).empty());
  show_top(*this);
  assert(!to_str(get_starting_position()).empty());

  draw_bottom(*this);
  show_selected_panel(*this);

  const bool show_semitransparent{true};
  show_squares(
    get_render_window(),
    m_layout.get_chess_board(),
    game_resources::get(),
    show_semitransparent
  );
  show_pieces(*this);

  assert(!to_str(get_starting_position()).empty());
}

void draw_bottom(options_view& v)
{
  draw_bottom_header(v);
  draw_bottom_row(v, side::lhs);
  draw_bottom_row(v, side::rhs);
}

void draw_bottom_header(options_view& v)
{
  const auto& layout{v.get_layout()};
  {
    const auto& screen_rect = layout.get_controls_label();
    sf::RectangleShape rectangle;

    set_rect(rectangle, screen_rect);
    rectangle.setTexture(
      &get_game_option_icon(
        options_view_item::left_controls
      )
    );
    // Zoom in
    rectangle.setTextureRect(
      sf::IntRect(
        0,
        rectangle.getTexture()->getSize().y / 4,
        rectangle.getTexture()->getSize().x,
        rectangle.getTexture()->getSize().y / 2
      )
    );
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    text.setString("Controls");
    set_text_position(text, screen_rect);
    get_render_window().draw(text);

    // Smaller
    text.setCharacterSize(text.getCharacterSize() - 2);
    set_text_position(text, screen_rect);
    text.setFillColor(sf::Color::White);
    get_render_window().draw(text);

  }
}

void draw_bottom_row(options_view& v, const side player_side)
{
  const auto& layout{v.get_layout()};
  // The icon
  {

    const auto screen_rect{
      layout.get_controller_type_value(player_side)
    };
    const physical_controller_type t{
      get_physical_controller_type(player_side)
    };
    draw_fancy_physical_controller_type(t, screen_rect);

    /*
    sf::RectangleShape rectangle;
    set_rect(rectangle, screen_rect);
    rectangle.setTexture(
      &game_resources::get().get_physical_controller_textures().get_fancy(t)
    );
    // Zoom in
    rectangle.setTextureRect(
      sf::IntRect(
        0,
        rectangle.getTexture()->getSize().y / 4,
        rectangle.getTexture()->getSize().x,
        rectangle.getTexture()->getSize().y / 2
      )
    );
    get_render_window().draw(rectangle);
    */
    // Text
    sf::Text text;
    const auto text_rect{screen_rect};
    text.setString(to_str(t));
    v.set_text_style(text);
    set_text_position(text, text_rect);
    get_render_window().draw(text);

    // Smaller
    text.setCharacterSize(text.getCharacterSize() - 2);
    set_text_position(text, text_rect);
    text.setFillColor(sf::Color::White);
    get_render_window().draw(text);
  }
}

void draw_game_speed(options_view& v)
{
  const auto& layout = v.get_layout();
  // game speed label
  {
    const auto& screen_rect = layout.get_game_speed_label();
    sf::RectangleShape rectangle;
    set_rect(rectangle, screen_rect);
    rectangle.setTexture(
      &get_game_option_icon(
        options_view_item::game_speed
      )
    );
    // Zoom in
    rectangle.setTextureRect(
      sf::IntRect(
        0,
        rectangle.getTexture()->getSize().y / 4,
        rectangle.getTexture()->getSize().x,
        rectangle.getTexture()->getSize().y / 2
      )
    );
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    text.setString("Game speed");
    set_text_position(text, screen_rect);
    get_render_window().draw(text);

    text.setCharacterSize(text.getCharacterSize() - 2);
    text.setFillColor(sf::Color::White);
    get_render_window().draw(text);
  }
  // game speed value
  {
    const auto& screen_rect = layout.get_game_speed_value();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_strip_texture(chess_color::black)
    );
    set_rect(rectangle, screen_rect);
    get_render_window().draw(rectangle);

    draw_big_text(to_str(game_options::get().get_game_speed()), screen_rect);
    /*
    sf::Text text;
    v.set_text_style(text);


    text.setString(to_str(game_options::get().get_game_speed()));
    set_text_position(text, screen_rect);
    get_render_window().draw(text);
    */
  }
}


void show_pieces(options_view& view)
{
  show_pieces(
    get_starting_pieces(game_options::get().get_starting_position()),
    get_render_window(),
    view.get_layout().get_chess_board(),
    game_options::get().do_show_selected()
  );
}

void show_starting_position(options_view& v)
{
  const auto& layout = v.get_layout();
  // starting pos label
  {
    const auto& screen_rect = layout.get_starting_pos_label();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_game_option_icon(
        options_view_item::starting_position
      )
    );
    set_rect(rectangle, screen_rect);
    // Zoom in
    rectangle.setTextureRect(
      sf::IntRect(
        0,
        rectangle.getTexture()->getSize().y / 4,
        rectangle.getTexture()->getSize().x,
        rectangle.getTexture()->getSize().y / 2
      )
    );
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    text.setString("Starting position");
    set_text_position(text, screen_rect);
    get_render_window().draw(text);

    text.setCharacterSize(text.getCharacterSize() - 2);
    text.setFillColor(sf::Color::White);
    get_render_window().draw(text);
  }
  // starting pos value
  {
    const auto& screen_rect = layout.get_starting_pos_value();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_strip_texture(chess_color::white)
    );
    set_rect(rectangle, screen_rect);
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    text.setString(to_str(get_starting_position()));
    set_text_position(text, screen_rect);
    get_render_window().draw(text);
  }


}

void show_top(options_view& v)
{
  assert(!to_str(get_starting_position()).empty());

  draw_game_speed(v);
  show_music_volume(v);
  show_sound_effects_volume(v);
  show_starting_position(v);

  assert(!to_str(get_starting_position()).empty());
}


void show_layout_panels(options_view& v)
{
  for (const auto& screen_rect: get_panels(v.get_layout()))
  {
    sf::RectangleShape rectangle;
    set_rect(rectangle, screen_rect);
    rectangle.setFillColor(sf::Color(255, 255, 255, 128));
    get_render_window().draw(rectangle);
  }
}

void show_music_volume(options_view& v)
{
  const auto& layout = v.get_layout();
  // music volume label
  {
    const auto& screen_rect = layout.get_music_volume_label();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_game_option_icon(
        options_view_item::music_volume
      )
    );
    set_rect(rectangle, screen_rect);
    // Zoom in
    rectangle.setTextureRect(
      sf::IntRect(
        0,
        rectangle.getTexture()->getSize().y / 4,
        rectangle.getTexture()->getSize().x,
        rectangle.getTexture()->getSize().y / 2
      )
    );
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    text.setString("Music volume");
    set_text_position(text, screen_rect);
    get_render_window().draw(text);

    text.setCharacterSize(text.getCharacterSize() - 2);
    text.setFillColor(sf::Color::White);
    get_render_window().draw(text);
  }
  // music volume value
  {
    const auto& screen_rect = layout.get_music_volume_value();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_strip_texture(chess_color::white)
    );
    set_rect(rectangle, screen_rect);
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    std::stringstream s;
    s << get_music_volume() << " %";
    text.setString(s.str());
    set_text_position(text, screen_rect);
    get_render_window().draw(text);
  }
}

void show_selected_panel(options_view& v)
{
  const auto select_rect{
    v.get_layout().get_selectable_rect(
      v.get_selected()
    )
  };
  draw_outline(select_rect);
  /*
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
  */
}

void show_sound_effects_volume(options_view& v)
{
  const auto& layout = v.get_layout();
  // sound effects volume label
  {
    const auto& screen_rect = layout.get_sound_effects_volume_label();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_game_option_icon(
        options_view_item::sound_effects_volume
      )
    );
    // Zoom in
    rectangle.setTextureRect(
      sf::IntRect(
        0,
        rectangle.getTexture()->getSize().y / 4,
        rectangle.getTexture()->getSize().x,
        rectangle.getTexture()->getSize().y / 2
      )
    );
    set_rect(rectangle, screen_rect);
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    text.setString("Sound effects volume");
    set_text_position(text, screen_rect);
    get_render_window().draw(text);

    text.setCharacterSize(text.getCharacterSize() - 2);
    text.setFillColor(sf::Color::White);
    get_render_window().draw(text);
  }
  // sound effects volume value
  {
    const auto& screen_rect = layout.get_sound_effects_volume_value();
    sf::RectangleShape rectangle;
    rectangle.setTexture(
      &get_strip_texture(chess_color::black)
    );
    set_rect(rectangle, screen_rect);
    get_render_window().draw(rectangle);

    sf::Text text;
    v.set_text_style(text);
    std::stringstream s;
    s << get_sound_effects_volume() << " %";
    text.setString(s.str());
    set_text_position(text, screen_rect);
    get_render_window().draw(text);
  }
}

void options_view::start()
{
  m_next_state.reset();
}

void options_view::stop()
{
  m_next_state.reset();
}

void options_view::tick()
{
  // Nothing here yet
}


#endif // LOGIC_ONLY
