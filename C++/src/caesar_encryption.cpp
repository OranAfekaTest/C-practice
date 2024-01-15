#include "caesar_encryption.hpp"
#include <algorithm> // transform
#include <iostream>
#include <string> // string::iterator

namespace encryptions
{
    
CaesarEncryption::CaesarEncryption(unsigned char a_key)
: m_key(a_key % 26)
{}

void CaesarEncryption::encode(Message const& a_plain, Message& a_cipher)
{
    CaesarRotation cr (m_key);
    a_cipher = a_plain;
    std::transform(a_cipher.begin(), a_cipher.end(), a_cipher.begin(), cr);
}
} // encryptions