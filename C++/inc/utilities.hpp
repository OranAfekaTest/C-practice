#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream> // ostream
#include <SFML/Graphics.hpp> // vector2f
#include <random> // default_random_engine, normal_distribution

namespace utils
{

struct Score
{
    uint32_t m_points = 0;
    uint64_t m_time = 0;
    char m_name[16];

    Score& operator+=(Score const& a_other)
    {
        m_points += a_other.m_points;
        m_time += a_other.m_time;
        return *this;
    }
};

bool score_compare(Score const& a_first, Score const& a_second);

class Random
{
public:
    Random();
    ~Random() = default;

    float normal_distribution(float a_mean, float a_standart_deviation);
    float uniform_real_distribution(float a_from, float a_to);

private:
    std::default_random_engine m_generator;
};

template <typename T>
T clamp(T a_val, T a_min, T a_max);

template <typename T>
T clamp(T a_val, T a_min, T a_max)
{
    return std::max(a_min,(std::min(a_val, a_max)));
}

std::ostream& operator<<(std::ostream& a_out, sf::Vector2f const& a_vector);
float random(float a_from, float a_to);
void normalize_vector(sf::Vector2f& a_vector);
} // utils

#endif // UTILS_HPP