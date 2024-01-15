#ifndef __MESSAGE_SOURCE__
#define __MESSAGE_SOURCE__

#include "message.hpp"

namespace encryptions
{
class MessageSource
{
public:
    ~MessageSource() = default;

    virtual Message* receive() = 0;

protected:
    MessageSource() = default;
    MessageSource(MessageSource const&) = default;
    MessageSource& operator=(MessageSource const&) = default;
};

} //encryptions
#endif //__MESSAGE_DESTINATION__