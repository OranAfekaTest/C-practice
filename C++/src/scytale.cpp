#include "scytale.hpp"
namespace encryptions
{
static std::string generate_key(size_t a_key)
{
    std::string result = "";
    for (size_t i = 0; i < a_key; i++)
    {
        result += (char)(i + 48);
    }
    return result;
}

Scytale::Scytale(size_t a_key)
: m_lisper(generate_key(a_key))
{}

void Scytale::encode(Message const& a_plain, Message& a_cipher)
{
    m_lisper.encode(a_plain, a_cipher);
}
} //encryptions