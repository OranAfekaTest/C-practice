#include "hud.hpp"


HUD::HUD(sf::RenderWindow& a_window, sf::Font const& a_font, unsigned int a_text_size)
: m_window{a_window}
, m_sheet{{(float)a_window.getSize().x, (float)a_window.getSize().y / 10}}
, m_score{"0", a_font, a_text_size}
, m_timer{"00:00", a_font, a_text_size}
, m_lives{"3", a_font, a_text_size}
{
    m_sheet.setOrigin(m_sheet.getSize().x / 2, m_sheet.getSize().y / 2);
    
    // set colors
    m_sheet.setFillColor({0 , 0, 60});
    m_score.setFillColor(sf::Color::White);
    m_timer.setFillColor(sf::Color::White);
    m_lives.setFillColor(sf::Color::White);
    
    // set styles
    m_score.setStyle(sf::Text::Bold);
    m_timer.setStyle(sf::Text::Bold);
    m_lives.setStyle(sf::Text::Bold);
    
    // set positions
    m_sheet.setPosition(m_sheet.getOrigin());
    m_score.setPosition(10 , 7);
    m_timer.setPosition(m_sheet.getSize().x / 2 - 50, 7);
    m_lives.setPosition(m_sheet.getSize().x - 30, 7);
}


HUD::~HUD()
{
}

void HUD::draw()
{
    m_window.draw(m_sheet);
    m_window.draw(m_score);
    m_window.draw(m_timer);
    m_window.draw(m_lives);
}

void HUD::update(float a_delta_time, int a_points, uint8_t a_lives)
{
    std::string minutes = std::to_string((int)a_delta_time / 60);
    if(minutes.size() == 1)
    {
        minutes = "0" + minutes;
    }
    std::string seconds = std::to_string((int)a_delta_time % 60);
    if(seconds.size() == 1)
    {
        seconds = "0" + seconds;
    }
    m_timer.setString(minutes + ":" + seconds);
    m_score.setString(std::to_string(a_points));
    m_lives.setString(std::to_string(a_lives));
}
void HUD::write_to_screen(std::string const& a_text ,sf::Color const& a_color)
{
    sf::Text text{a_text, *m_score.getFont(), 100};
    text.setFillColor(a_color);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
    m_window.draw(text);
    m_window.display();
}