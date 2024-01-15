#include "game.hpp"
#include "level.hpp"
#include "opening_screen.hpp"
#include "top_ten.hpp"
#include "masonry.hpp"
#include "state_machine.hpp"

#include <SFML/Graphics.hpp> // all sf::thingies
#include <vector> // Pawn vector

Game::Game(const unsigned a_width, const unsigned a_hight)
: m_window{sf::VideoMode(a_width, a_hight), "Arkanoid"}
{
    load_resources();
}

Game::~Game()
{
}

void Game::load_resources()
{
    m_font.loadFromFile("../../inc/resources/fonts/GothStencil_Premium.ttf");
    m_bg_image.loadFromFile("../../inc/resources/sprites/background.jpg");
    m_button_texture.loadFromFile("../../inc/resources/sprites/button.png");
}

sf::RenderWindow& Game::window()
{
    return m_window;
}

void Game::start()
{
    sf::Vector2f paddle_start_pos(m_window.getSize().x / 2 , m_window.getSize().y - 50);
    float ball_speed = 200, ball_size = 10, paddle_speed = 150;
    
    // Init levels
    StateMachine* sm = StateMachine::get_instance();
    Masonry* masonry = Masonry::get_instance();
    OpeningScreen main_screen{m_window, m_bg_image, m_button_texture, m_font, 50};
    TopTen top_ten{m_window, m_font, 30};
    Level first_level(m_window, ball_speed, ball_size, paddle_speed, paddle_start_pos, m_font);

    // sm->add_state(std::move(main_screen));
    (void)masonry;
    (void)sm;
    // float delta_time = 0;
    // sf::Clock clock;
    // run the program as long as the window is open
    while (m_window.isOpen())
    {
        // delta_time = clock.restart().asSeconds();
        main_screen.render();
        
        masonry->make_rectangle(first_level);
        m_score += first_level.play();

        masonry->make_triangle(first_level);
        m_score += first_level.play();

        masonry->make_vertical_stripes(first_level);
        m_score += first_level.play();

        masonry->make_horizontal_stripes(first_level);
        m_score += first_level.play();
        
        top_ten.render(m_score);
    }

}
