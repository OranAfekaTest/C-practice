#ifndef TOP_TEN_HPP
#define TOP_TEN_HPP

#include "utilities.hpp"
#include "text_box.hpp"

#include <list>
#include <vector>
#include <SFML/Graphics.hpp> // all sf::thingies

class TopTen
{
public:
    TopTen(sf::RenderWindow& a_window, sf::Font const& a_font, unsigned int a_text_size);
    ~TopTen() = default;

    void render(utils::Score& a_new_score);

private:
    void write_scores();
    void init_text();
    bool check_nominate(utils::Score const& a_new_score);
    void update_list(utils::Score const& a_new_score);
    void update_text_vector();
    void save_file();
    void load_file();

private:
    sf::RenderWindow& m_window;
    std::list<utils::Score> m_scores;
    std::vector<sf::Text> m_scores_text;
    TextBox m_name_input_text_box;
};

#endif // TOP_TEN_HPP