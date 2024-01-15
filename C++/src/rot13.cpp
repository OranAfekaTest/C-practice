#include "rot13.hpp"

namespace encryptions
{
Rot13::Rot13()
: m_caeser(13)
{}

void Rot13::encode(Message const& a_plain, Message& a_cipher)
{
    m_caeser.encode(a_plain, a_cipher);
}

} // encryptions