#ifndef SCORE_HPP
#define SCORE_HPP

#include <cstdint> // uint32_t uint64_t
#include <string> // set_name

class Score
{
public:
    void set_name(std::string const& a_name);
    Score& operator+=(Score const& a_other);
    void set_score(uint32_t a_points, uint64_t a_time);
    friend bool score_compare(Score const& a_first, Score const& a_second);

private:
    uint32_t m_points = 0;
    uint64_t m_time = 0;
    char m_name[16];
};

bool score_compare(Score const& a_first, Score const& a_second);

#endif // SCORE_HPP