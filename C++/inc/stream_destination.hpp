#ifndef __STREAM_DESTINATION__
#define __STREAM_DESTINATION__

#include "message_destination.hpp"

#include <iostream> // ostream

namespace encryptions
{
class StreamDestination : public MessageDestination
{
public:
    virtual ~StreamDestination() = default;

    void send(Message const& a_message) override;

    //virtual StreamDestination& operator<<(Message const& a_message)= 0;
protected:
    StreamDestination(std::ostream& a_out_stream);

private:
    std::ostream& m_out_stream;
};

} //encryptions
#endif //__STREAM_DESTINATION__