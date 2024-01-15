#include "score.hpp"

#include <cstring>

Score& Score::operator+=(Score const& a_other)
{
    m_points += a_other.m_points;
    m_time += a_other.m_time;
    return *this;
}

void Score::set_name(std::string const& a_name)
{
    strcpy(m_name, a_name.c_str());
}

void Score::set_score(uint32_t a_points, uint64_t a_time)
{
    m_points += a_points;
    m_time = a_time;
}

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
