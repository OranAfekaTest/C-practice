#ifndef __CONSOLE_SOURCE__
#define __CONSOLE_SOURCE__

#include "stream_source.hpp"

namespace encryptions
{
class ConsoleSource: public StreamSource
{
public:
    ~ConsoleSource() = default;
    ConsoleSource();

    //virtual StreamSource& operator>>(Message const& a_message) = 0;

};
    
} //encryptions
#endif //__CONSOLE_SOURCE__