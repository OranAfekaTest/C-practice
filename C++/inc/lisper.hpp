#ifndef __LISPER__
#define __LISPER__

#include "encoder.hpp"
#include "message.hpp"

namespace encryptions
{
class Lisper : public Encoder
{
public:
    Lisper(std::string a_key);
    ~Lisper() = default;

    void encode(Message const& a_plain, Message& a_cipher) override;

private:
    std::string m_key;
};
} // encryptions

#endif //__LISPER__