#ifndef __PRECIOUS_STONE__
#define __PRECIOUS_STONE__

#include "message_source.hpp"
#include "message_destination.hpp"
#include "encoder.hpp"

namespace encryptions
{
class PreciousStone
{
public:
    ~PreciousStone() = default;
    PreciousStone(MessageSource& a_source, MessageDestination& a_destination, Encoder& a_encoder);
    
    void execute();

private:
    MessageSource& m_source;
    MessageDestination& m_destination;
    Encoder& m_encoder;
};

} //encryptions
#endif //__PRECIOUS_STONE__