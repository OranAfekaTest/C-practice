#include "uppercase.hpp"

#include <algorithm> // transform
#include <iostream>
#include <string> // string::iterator

namespace encryptions
{
    static unsigned char uppercase_char(unsigned char c)
    {
        if(96 < c and c < 123)
        {
            c -= 32;
        }
        std::cout << c;
        return c;
    }

    void Uppercase::encode(Message const& a_plain, Message& a_cipher) 
    {
        a_cipher = a_plain;
        std::transform(a_cipher.begin(), a_cipher.end(), a_cipher.begin(), uppercase_char);
    }

} // encryptions