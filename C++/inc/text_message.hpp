#ifndef __TEXT_MESSAGE__
#define __TEXT_MESSAGE__

#include "message.hpp"

#include <string>

namespace encryptions
{
class TextMessage : public Message {
public:
    ~TextMessage() override = default;
    explicit TextMessage(Message const& a_cpy);
    Message& operator=(Message const& a_cpy) override;

    TextMessage();
    TextMessage(const char* a_text);
    // TextMessage(std::string a_text);

    std::string::iterator begin() override;
    std::string::iterator end() override;
    std::string::const_iterator begin() const override;
    std::string::const_iterator end() const override;

    bool operator==(std::string const& a_cmp) const;
    bool operator!=(std::string const& a_cmp) const;

private:
    std::string m_text;
};
}

#endif // __TEXT_MESSAGE__