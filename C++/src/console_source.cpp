#include "console_source.hpp"

#include <iostream> // cin

namespace encryptions
{

ConsoleSource::ConsoleSource()
: StreamSource(std::cin)
{}

} //encryptions