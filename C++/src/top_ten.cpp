#include "top_ten.hpp"

#include <cstring> // strcpy
#include <fstream> // ofstream / ifstream

TopTen::TopTen(sf::RenderWindow& a_window, sf::Font const& a_font, unsigned int a_text_size)
: m_window{a_window}
, m_scores_text{33, {"--------", a_font, a_text_size}}
, m_name_input_text_box{a_font}
{
    init_text();
    load_file();
}

void TopTen::init_text()
{
    float row_offset = 30;

    for (size_t i = 0; i < 11; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_scores_text[j + i * 3].setOrigin(m_scores_text[j + i * 3].getGlobalBounds().width / 2, m_scores_text[j + i * 3].getGlobalBounds().height / 2);
            m_scores_text[j + i * 3].setFillColor(sf::Color::Yellow);
            m_scores_text[j + i * 3].setOutlineColor(sf::Color::Black);
            m_scores_text[j + i * 3].setOutlineThickness(2);
            m_scores_text[j + i * 3].setPosition({m_window.getSize().x / 6 + (float)j * (m_window.getSize().x / 3),
            row_offset + (float)i * (row_offset + m_scores_text[j + i * 3].getGlobalBounds().height)});
            if(i == 0)
            {
                m_scores_text[j].setStyle(sf::Text::Bold | sf::Text::Underlined);
                switch (j)
                {
                case 0:
                    m_scores_text[j].setString("Name");
                    break;
                
                case 1:
                    m_scores_text[j].setString("Points");
                    break;
                
                case 2:
                    m_scores_text[j].setString("Time");
                    break;
                
                default:
                    break;
                }
            }
        }
        
    }
    
}

void TopTen::save_file()
{
    std::ofstream binaryFile("top10.dat", std::ios::out | std::ios::binary);

    if (binaryFile.is_open()) {
        
        for (const utils::Score& score : m_scores) {
            binaryFile.write(reinterpret_cast<const char*>(&score), sizeof(score));
        }

        binaryFile.close();
    }
}

void TopTen::load_file()
{
    std::ifstream binaryFile("top10.dat", std::ios::in | std::ios::binary);

    if (binaryFile.is_open()) {
        utils::Score score;
        while (binaryFile.read(reinterpret_cast<char*>(&score), sizeof(score))) {
            m_scores.push_back(score);
        }

        binaryFile.close();
        update_text_vector();
    }
}

void TopTen::update_list(utils::Score const& a_new_score)
{
    m_scores.push_back(std::move(a_new_score));
    m_scores.sort(utils::score_compare);
    if(m_scores.size() > 10)
    {
        m_scores.pop_back();
    }
    update_text_vector();
    save_file();
}

bool TopTen::check_nominate(utils::Score const& a_new_score)
{
    if(m_scores.size() < 10)
    {
        return true;
    }
    utils::Score last_place = *(--m_scores.end());
    return utils::score_compare(a_new_score, last_place);
}

void TopTen::update_text_vector()
{
    size_t vector_index = 3;
    for(utils::Score const& score : m_scores)
    {
        m_scores_text[vector_index++].setString(score.m_name);
        m_scores_text[vector_index++].setString(std::to_string(score.m_points));
        m_scores_text[vector_index++].setString(std::to_string(score.m_time));
    }
}

void TopTen::render(utils::Score& a_new_score)
{
    if(check_nominate(a_new_score))
    {
        strcpy(a_new_score.m_name, m_name_input_text_box.input_player_name().c_str());
        update_list(a_new_score);
    }
    while(m_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (m_window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if(event.type == sf::Event::KeyPressed)
            {
                return;
            }

            if(event.type == sf::Event::Closed)
            {
                m_window.close();
            }

        }

        // clear the window with blue color
        m_window.clear(sf::Color::Blue);

        // draw everything here...
        for (sf::Text& text : m_scores_text)
        {
            m_window.draw(text);
        }
        
        // end the current frame
        m_window.display();
    }
}