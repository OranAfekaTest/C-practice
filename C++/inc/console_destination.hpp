#ifndef __CONSOLE_DESTINATION__
#define __CONSOL_DESTINATION__

#include "stream_destination.hpp"

namespace encryptions
{
class ConsoleDestination : public StreamDestination
{
public:
    ~ConsoleDestination() = default;
    ConsoleDestination();

    //ConsoleDestination& operator<<(Message const& a_message);

};

} //encryptions
#endif //__CONSOL_DESTINATION__