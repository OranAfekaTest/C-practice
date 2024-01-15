#include "masonry.hpp"

#include "utilities.hpp" // Random

void Masonry::make_rectangle(Level& a_level, unsigned a_rows, unsigned a_cols, unsigned a_border_offset, unsigned a_spaces_size)
{
    float brick_w = a_level.m_window.getSize().x / a_cols - a_border_offset;
    float brick_h = brick_w / 4;
    std::cout << "brick_w= " << brick_w << " brick_h= " << brick_h << '\n';
    a_border_offset = (a_border_offset * a_cols) / 2;
    utils::Random rand;
    a_level.m_bricks.clear();
    a_level.m_bricks.reserve(a_rows * a_cols);
    for (size_t i = 0; i < a_rows; ++i)
    {
        sf::Color color(utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255));
        for (size_t j = 0; j < a_cols; ++j)
        {            
            a_level.m_bricks.emplace_back(a_level.m_window, sf::Vector2f{brick_w, brick_h},
            sf::Vector2f{a_border_offset + j * (brick_w + a_spaces_size),
            a_border_offset + a_spaces_size + i * (brick_h + a_spaces_size)},
            color);
        }
    }
}

void Masonry::make_triangle(Level& a_level, unsigned a_rows, unsigned a_cols, unsigned a_border_offset, unsigned a_spaces_size)
{
    float brick_w = a_level.m_window.getSize().x / a_cols - a_border_offset;
    float brick_h = brick_w / 4;
    std::cout << "a_rows= " << a_rows << " a_cols= " << a_cols << '\n';
    a_border_offset = (a_border_offset * a_cols) / 2;
    utils::Random rand;
    a_level.m_bricks.clear();
    a_level.m_bricks.reserve(a_rows * a_cols);
    for (size_t i = 0; i < a_rows; ++i)
    {
        sf::Color color(utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255));
        for (size_t j = 0; j < i + 1; ++j)
        {
            if(i == a_rows -1 and !(j == a_cols -1))
            {
                sf::Color color(126, 129, 115);
                a_level.m_bricks.emplace_back(a_level.m_window, sf::Vector2f{brick_w, brick_h},
                sf::Vector2f{a_border_offset + j * (brick_w + a_spaces_size),
                a_border_offset + a_spaces_size + i * (brick_h + a_spaces_size)},
                color, 3);
            }
            else
            {
                a_level.m_bricks.emplace_back(a_level.m_window, sf::Vector2f{brick_w, brick_h},
                sf::Vector2f{a_border_offset + j * (brick_w + a_spaces_size),
                a_border_offset + a_spaces_size + i * (brick_h + a_spaces_size)},
                color);
            }
            std::cout << "i= " << i << " j= " << j << '\n';
        }
    }
}

void Masonry::make_vertical_stripes(Level& a_level, unsigned a_rows, unsigned a_cols, unsigned a_border_offset, unsigned a_spaces_size)
{
    float brick_w = a_level.m_window.getSize().x / a_cols - a_border_offset;
    float brick_h = brick_w / 4;
    std::cout << "brick_w= " << brick_w << " brick_h= " << brick_h << '\n';
    a_border_offset = (a_border_offset * a_cols) / 2;
    utils::Random rand;
    a_level.m_bricks.clear();
    a_level.m_bricks.reserve(a_rows * a_cols);
    for (size_t i = 0; i < a_rows; ++i)
    {
        sf::Color color(utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255));
        for (size_t j = 0; j < a_cols; ++j)
        {        
            if(j % 2 == 0)
            {
                a_level.m_bricks.emplace_back(a_level.m_window, sf::Vector2f{brick_w, brick_h},
                sf::Vector2f{a_border_offset + j * (brick_w + a_spaces_size),
                a_border_offset + a_spaces_size + i * (brick_h + a_spaces_size)},
                color);
            }    
        }
    }
}

void Masonry::make_horizontal_stripes(Level& a_level, unsigned a_rows, unsigned a_cols, unsigned a_border_offset, unsigned a_spaces_size)
{
    float brick_w = a_level.m_window.getSize().x / a_cols - a_border_offset;
    float brick_h = brick_w / 4;
    std::cout << "brick_w= " << brick_w << " brick_h= " << brick_h << '\n';
    a_border_offset = (a_border_offset * a_cols) / 2;
    utils::Random rand;
    a_level.m_bricks.clear();
    a_level.m_bricks.reserve(a_rows * a_cols);
    for (size_t i = 0; i < a_rows; ++i)
    {
        sf::Color color(utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255), utils::clamp<int>(rand.normal_distribution(127, 127), 0, 255));
        for (size_t j = 0; j < a_cols; ++j)
        {        
            if(i % 2 == 0)
            {
                a_level.m_bricks.emplace_back(a_level.m_window, sf::Vector2f{brick_w, brick_h},
                sf::Vector2f{a_border_offset + j * (brick_w + a_spaces_size),
                a_border_offset + a_spaces_size + i * (brick_h + a_spaces_size)},
                color);
            }    
        }
    }
}    