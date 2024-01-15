#ifndef __STREAM_SOURCE__
#define __STREAM_SOURCE__

#include "message_source.hpp"

#include <iostream> // istream

namespace encryptions
{
class StreamSource: public MessageSource
{
public:
    ~StreamSource() = default;

    Message* receive() override;

    //virtual StreamSource& operator>>(Message const& a_message) = 0;
protected:
    StreamSource(std::istream& a_in_stream);

private:
    std::istream& m_in_stream;
};
    
} //encryptions
#endif //__STREAM_SOURCE__