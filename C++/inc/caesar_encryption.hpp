#ifndef __CAESAR_ENRYPTION__
#define __CAESAR_ENRYPTION__

#include "encoder.hpp"
#include "message.hpp"
namespace encryptions
{
class CaesarEncryption : public Encoder
{
public:
    CaesarEncryption(unsigned char a_key);
    ~CaesarEncryption() = default;

    void encode(Message const& a_plain, Message& a_cipher) override;

private:
    unsigned char m_key;
};

class CaesarRotation
{
public:
    CaesarRotation(unsigned char a_key) : m_key(a_key){}
    char operator()(unsigned char a_char)
    {
        //encrypt for lowercase letter
        if('a' <= a_char and a_char <= 'z')
        {
            a_char += m_key;
            if('z' < a_char)
            {
                a_char -= 26;
            }  
        }
        //encrypt for uppercase letter
        else if('A' <= a_char and a_char <= 'Z')
        {
            a_char += m_key;
            if('Z' < a_char)
            {
                a_char -= 26;
            }
        }
        return a_char;
    }

private:
    unsigned char m_key;
};
} // encryptions
#endif //__CAESAR_ENRYPTION__