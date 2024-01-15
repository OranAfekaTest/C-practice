#ifndef __UPPERCASE__
#define __UPPERCASE__

#include "encoder.hpp"
#include "message.hpp"

namespace encryptions
{
class Uppercase : public Encoder {
public:
    void encode(Message const& a_plain, Message& a_cipher) override;
};
} // encryptions
#endif // __UPPERCASE__