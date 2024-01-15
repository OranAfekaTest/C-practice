#include "translator.hpp"

#include <algorithm> // transform

CharTranslator::CharTranslator(std::string a_keys, std::string a_values, size_t a_size)
{
    for (size_t i = 0; i < a_size; ++i)
    {
        m_char_map[toupper(a_keys[i])] = a_values[i];
    }
}

void CharTranslator::translate(Message& a_message)
{
    TransObject tx{m_char_map};
    std::transform(a_message.begin(), a_message.end(), a_message.begin(), tx);
}
