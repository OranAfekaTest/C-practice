#ifndef __MESSAGE_DESTINATION__
#define __MESSAGE_DESTINATION__

#include "message.hpp"

namespace encryptions
{
class MessageDestination
{
public:
    virtual ~MessageDestination() = default;

    virtual void send(Message const& a_message) = 0;

    //virtual MessageDestination& operator<<(Message const& a_message)= 0;
protected:
    MessageDestination() = default;
    MessageDestination(MessageDestination const&) = default;
    MessageDestination& operator=(MessageDestination const&) = default;
};

} //encryptions
#endif //__MESSAGE_DESTINATION__