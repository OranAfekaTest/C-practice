#ifndef __ASTRIXREPLACER__
#define __ASTRIXREPLACER__

#include "message.hpp"
#include "encoder.hpp"
#include "translator.hpp"

class AstrixReplacer : public Encoder
{
public:
    AstrixReplacer();
    void encode(Message const& a_plain, Message& a_cipher);

private:
    CharTranslator m_translator;
};

#endif // __ASTRIXREPLACER__