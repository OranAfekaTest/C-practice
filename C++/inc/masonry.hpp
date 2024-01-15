#ifndef MASONRY_HPP
#define MASONRY_HPP

#include "level.hpp"
#include "singleton.hpp"

#include <SFML/Graphics.hpp> // all sf::thingies

class Level;
class Masonry : public Singleton<Masonry>
{
    friend class Singleton<Masonry>;

public:
    // Masonry(sf::RenderWindow& a_window);
    ~Masonry() = default;

    void make_rectangle(Level& a_level, unsigned a_rows = 4, unsigned a_cols = 10, unsigned a_border_offset = 15, unsigned a_spaces_size = 10);
    void make_triangle(Level& a_level, unsigned a_rows = 8, unsigned a_cols = 8, unsigned a_border_offset = 15, unsigned a_spaces_size = 10);
    void make_vertical_stripes(Level& a_level, unsigned a_rows = 10, unsigned a_cols = 11, unsigned a_border_offset = 15, unsigned a_spaces_size = 10);
    void make_horizontal_stripes(Level& a_level, unsigned a_rows = 7, unsigned a_cols = 10, unsigned a_border_offset = 15, unsigned a_spaces_size = 10);

private:
    // sf::RenderWindow& m_window;
};

#endif // MASONRY_HPP