#include "message.hpp"

std::ostream& operator<<(std::ostream& a_out, Message const& a_message)
{
    std::string::const_iterator itr = a_message.begin();
    while(itr != a_message.end())
    {
        a_out << *itr;
        ++itr;
    }
    return a_out;
}