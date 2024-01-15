#ifndef __SCYTALE__
#define __SCYTALE__

#include "encoder.hpp"
#include "message.hpp"
#include "lisper.hpp"
namespace encryptions
{
class Scytale : public Encoder
{
public:
    Scytale(size_t a_key);
    ~Scytale() = default;

    void encode(Message const& a_plain, Message& a_cipher);

private:
    Lisper m_lisper;
};
} //encryptions
#endif //__SCYTALE__