#include "utilities.hpp"

#include <random> // default_random_engine, normal_distribution
#include <SFML/Graphics.hpp> // vector2f
#include <cmath> //fabsf

namespace utils
{
bool score_compare(Score const& a_first, Score const& a_second)
{
    if(a_first.m_points < a_second.m_points)
    {
        return false;
    }
    else if(a_second.m_points < a_first.m_points)
    {
        return true;
    }
    else if(a_first.m_time < a_second.m_time)
    {
        return true;
    }
    return false;
}

Random::Random()
: m_generator{}
{}

float Random::normal_distribution(float a_mean, float a_standart_deviation)
{
    std::normal_distribution<float> distribution(a_mean, a_standart_deviation);
    return distribution(m_generator);
}

float Random::uniform_real_distribution(float a_from, float a_to)
{
    std::uniform_real_distribution<float> distribution(a_from, a_to);
    return distribution(m_generator);
}

std::ostream& operator<<(std::ostream& a_out, sf::Vector2f const& a_vector)
{
    a_out << '(' << a_vector.x << ", " << a_vector.y << ')';
    return a_out;
}

float random(float a_from, float a_to)
{
    std::default_random_engine m_generator;
    std::uniform_real_distribution<float> distribution(a_from, a_to);
    return distribution(m_generator);
}

void normalize_vector(sf::Vector2f& a_vector)
{
    float length = sqrtf(powf(a_vector.x, 2) + powf(a_vector.y, 2));
    a_vector.x /= length;
    a_vector.y /= length;
}

} // utils