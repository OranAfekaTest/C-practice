#include "console_destination.hpp"

#include <iostream> // cout

namespace encryptions
{

ConsoleDestination::ConsoleDestination()
: StreamDestination(std::cout)
{}

} // encryptions