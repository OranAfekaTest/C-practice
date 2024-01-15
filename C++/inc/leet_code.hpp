#ifndef __LEET_CODE__
#define __LEET_CODE__

#include "encoder.hpp"
#include "message.hpp"
#include "translator.hpp"

class LeetCode : Encoder
{
public:
    LeetCode();
    void encode(Message const& a_plain, Message& a_cipher);

private:
    CharTranslator m_translator;
};



#endif // __LEET_CODE__