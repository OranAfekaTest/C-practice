#include "precious_stone.hpp"

namespace encryptions
{
PreciousStone::PreciousStone(MessageSource& a_source, MessageDestination& a_destination, Encoder& a_encoder)
: m_source{a_source}
, m_destination{a_destination}
, m_encoder{a_encoder}
{}
    
void PreciousStone::execute()
{
    Message* message = m_source.receive();
    m_encoder.encode(*message, *message);
    m_destination.send(*message);
    delete message;
}
} // encryptions