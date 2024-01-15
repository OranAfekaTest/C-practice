#ifndef __MEASSAGE__
#define __MEASSAGE__

#include <string>
#include <iostream>

class Message {
public:
    virtual ~Message() = default;
    virtual Message& operator=(Message const& a_cpy) = 0;

    virtual std::string::iterator begin() = 0;
    virtual std::string::iterator end() = 0;
    virtual std::string::const_iterator begin() const = 0;
    virtual std::string::const_iterator end() const = 0;

};

std::ostream& operator<<(std::ostream& a_out, Message const& a_message);

#endif // __MEASSAGE__