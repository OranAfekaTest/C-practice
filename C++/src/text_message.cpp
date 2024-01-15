#include "text_message.hpp"

namespace encryptions
{

    TextMessage::TextMessage()
    : m_text{""} 
    {}

    TextMessage::TextMessage(const char* a_text)
    : m_text{a_text} 
    {}

    // TextMessage::TextMessage(std::string a_text)
    // : m_text{a_text} 
    // {}
    
    TextMessage::TextMessage(Message const& a_cpy)
    {
        std::string::const_iterator itr = a_cpy.begin();
        while(itr != a_cpy.end())
        {
            m_text += *itr;
            ++itr;
        }
    }

    Message& TextMessage::operator=(Message const& a_cpy) 
    {
        if(this != &a_cpy)
        {
            TextMessage tmp{a_cpy};
            m_text = tmp.m_text;
        }
        return *this;
    }
    
    std::string::iterator TextMessage::begin() 
    {
        return m_text.begin();
    }

    std::string::iterator TextMessage::end()
    {
        return m_text.end();
    }

    std::string::const_iterator TextMessage::begin() const
    {
        return m_text.cbegin();
    }

    std::string::const_iterator TextMessage::end() const
    {
        return m_text.cend();
    }

    bool TextMessage::operator==(std::string const& a_cmp) const
    {
        std::cout << "this  text " << m_text << "\n";
        std::cout << "a_cmp text " << a_cmp << "\n";
        return m_text == a_cmp;
    }

    bool TextMessage::operator!=(std::string const& a_cmp) const
    {
        return !(*this == a_cmp);
    }
}