#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

#include "singleton.hpp"

#include <unordered_map>
#include <fstream> // ofstream, ifstream

template <typename Key, typename Value>
class FileParser : public Singleton<FileParser<Key, Value>>
{
public:
    void parse_map_into_file(std::unordered_map<Key, Value> const& a_map, std::ofstream& a_file, std::string const& delimiter);
    void parse_file_into_map(std::unordered_map<Key, Value>& a_map, std::ifstream& a_file, std::string const& delimiter);
};

template <typename Key, typename Value>
void FileParser<Key, Value>::parse_map_into_file(std::unordered_map<Key, Value> const& a_map, std::ofstream& a_file, std::string const& delimiter)
{
    if(a_file.is_open())
    {
        for(const auto& pair : a_map)
        {
            a_file << pair.first << delimiter << pair.second << '\n';
        }
    }
}

template <typename Key, typename Value>
void FileParser<Key, Value>::parse_file_into_map(std::unordered_map<Key, Value>& a_map, std::ifstream& a_file, std::string const& delimiter)
{
    std::string secret;
    std::string key;
    a_map.clear();
    while ( getline (a_file, secret) )
    {
        size_t pos = secret.find(delimiter);
        key = secret.substr(0, pos);
        secret.erase(0, pos + delimiter.length());
        //Should be Secret{secret}
        a_map[key] = std::stod(secret);
    }
}

#endif // FILE_PARSER_HPP