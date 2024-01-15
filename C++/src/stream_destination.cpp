#include "stream_destination.hpp"

namespace encryptions
{
StreamDestination::StreamDestination(std::ostream& a_out_stream)
: m_out_stream{a_out_stream}
{}

void StreamDestination::send(Message const& a_message)
{
    for (auto c : a_message)
    {
        m_out_stream << c;
    }
}

} //encryptions