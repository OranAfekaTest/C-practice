#ifndef __ENCODER__
#define __ENCODER__

#include "message.hpp"

class Encoder
{
public:
    virtual ~Encoder() = default;
    virtual void encode(Message const& a_plain, Message& a_cipher) = 0;
};

#endif // __ENCODER__