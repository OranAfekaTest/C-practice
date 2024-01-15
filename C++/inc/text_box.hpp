#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <SFML/Graphics.hpp>

class TextBox
{
public:
    TextBox(sf::Font const& a_font);
    ~TextBox() = default;

    std::string input_player_name();

private:
    sf::Text m_anounce_text;
    sf::Text m_input_text;
    std::string m_input_string;
};

#endif // TEXT_BOX_HPP