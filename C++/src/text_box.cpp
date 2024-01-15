#include "text_box.hpp"

TextBox::TextBox(sf::Font const& a_font)
: m_anounce_text{"Congratulations! you've made it\n to the top 10 boardlist", a_font}
, m_input_text{"", a_font}
{
    m_anounce_text.setOrigin(m_anounce_text.getGlobalBounds().width / 2, m_anounce_text.getGlobalBounds().height / 2);
    m_input_text.setOrigin(m_input_text.getGlobalBounds().width / 2, m_input_text.getGlobalBounds().height / 2);
}

std::string TextBox::input_player_name()
{
    sf::Clock clock;
    sf::RenderWindow window{{480 , 240}, "Enter Name"};
    m_anounce_text.setPosition(window.getSize().x / 2, m_anounce_text.getGlobalBounds().height);
    m_input_text.setPosition(window.getSize().x / 5, m_anounce_text.getGlobalBounds().height * 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered and m_input_string.size() < 16) 
            {
                if (std::isprint(event.text.unicode))
                {
                    m_input_string += event.text.unicode;
                }
            }
            else if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == sf::Keyboard::BackSpace) 
                {
                    if (!m_input_string.empty())
                    {
                        m_input_string.pop_back();
                    }
                }
                if (event.key.code == sf::Keyboard::Return) 
                {
                    if(!m_input_string.empty())
                    {
                        window.close();
                    }
                }
            }
        }

        static sf::Time text_effect_time;
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= sf::seconds(0.5f))
        {
            show_cursor = !show_cursor;
            text_effect_time = sf::Time::Zero;
        }

        m_input_text.setString(m_input_string + (show_cursor ? '_' : ' '));

        window.clear();
        window.draw(m_input_text);
        window.draw(m_anounce_text);
        window.display();
    }
    return m_input_string;
}