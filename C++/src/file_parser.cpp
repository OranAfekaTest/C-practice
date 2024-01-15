#include "file_parser.hpp"


void FileParser::parse_map_into_file(std::unordered_map const& a_map, std::ofstream a_file, std::string delimiter)
{
    if(a_file.is_open())
    {
        for(const auto& pair : a_map)
        {
            a_file << pair.first << delimiter << pair.second << '\n';
        }
    }
}

void FileParser::parse_file_into_map(std::unordered_map& a_map, std::ifstream a_file, std::string delimiter)
{
    std::string secret;
    std::string key;
    a_map.clear();
    while ( getline (a_file, secret) )
    {
        size_t pos = secret.find(delimiter);
        key = secret.substr(0, pos);
        secret.erase(0, pos + delimiter.length());
        a_map[key] = std::stod(secret);
    }
}