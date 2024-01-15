#include "opening_screen.hpp"

OpeningScreen::OpeningScreen(sf::RenderWindow& a_window, sf::Texture& a_bg_image, sf::Texture& a_button_texture, sf::Font const& a_font, float a_button_offset)
: m_window{a_window}
, m_background{static_cast<sf::Vector2f>(a_window.getSize())}
, m_logo{"Arkanoid", a_font, 200}
, m_play_button{a_window, {(float)(a_window.getSize().x / 2), (float)(a_window.getSize().y / 2 + a_button_offset)}, "Play", a_font, a_button_texture}
, m_quit_button{a_window, {(float)(a_window.getSize().x / 2), (float)(a_window.getSize().y / 2 + 3 * a_button_offset)}, "Quit", a_font, a_button_texture}
{
    m_background.setTexture(&a_bg_image);
    m_logo.setOrigin(m_logo.getGlobalBounds().width / 2, m_logo.getGlobalBounds().height / 2);
    m_logo.setPosition(a_window.getSize().x / 2, 100);
    m_logo.setFillColor(sf::Color::Magenta);
    m_logo.setOutlineColor(sf::Color::Black);
    m_logo.setOutlineThickness(20);
}

OpeningScreen::~OpeningScreen()
{
}

void OpeningScreen::render()
{
    // float delta_time = 0;
    // sf::Clock clock;
    m_button_clicked = false;
    while(m_window.isOpen() and not m_button_clicked)
    {
        // delta_time = clock.restart().asSeconds();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (m_window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        m_button_clicked |= m_play_button.update();
        m_button_clicked |= m_quit_button.update();

        // clear the window with dark green color
        m_window.clear(sf::Color(0, 30, 0));

        // draw everything here...
        m_window.draw(m_background);
        m_window.draw(m_logo);
        m_play_button.draw();
        m_quit_button.draw();

        // end the current frame
        m_window.display();
    }
}
