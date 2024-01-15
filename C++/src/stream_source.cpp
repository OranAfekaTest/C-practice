#include "stream_source.hpp"
#include "text_message.hpp"

#include <string>

#define MAX_INPUT_SIZE 256

namespace encryptions
{
StreamSource::StreamSource(std::istream& a_in_stream)
: m_in_stream{a_in_stream}
{}

Message* StreamSource::receive()
{
    char input [MAX_INPUT_SIZE];
    m_in_stream.getline(input, MAX_INPUT_SIZE);
    Message* message = new TextMessage(input);
    return message;
}

}