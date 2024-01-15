#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include "message.hpp"

#include <unordered_map>

class CharTranslator
{
public:
    CharTranslator(std::string a_keys, std::string a_values, size_t a_size);
    ~CharTranslator() = default;

    void translate(Message& a_message);

private:
    std::unordered_map<char, char> m_char_map;
};

class TransObject
{
public:
    TransObject(std::unordered_map<char, char>& a_char_map) : m_char_map(a_char_map){}
    char operator()(char a_char)
    {
        if(m_char_map.find(toupper(a_char)) != m_char_map.end())
        {
            return m_char_map[toupper(a_char)];
        }
        return a_char;
    }

private:
    std::unordered_map<char, char>& m_char_map;
};

#endif // __TRANSLATOR__