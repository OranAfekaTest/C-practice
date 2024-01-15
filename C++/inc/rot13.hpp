#ifndef __ROT13__
#define __ROT13__

#include "message.hpp"
#include "encoder.hpp"
#include "caesar_encryption.hpp"

namespace encryptions
{
class Rot13 : public Encoder
{
public:
    Rot13();
    void encode(Message const& a_plain, Message& a_cipher) override;

private:
    CaesarEncryption m_caeser;
};
} // encryptions
#endif // __ROT13__