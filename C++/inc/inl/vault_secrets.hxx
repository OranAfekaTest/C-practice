
#ifndef __SECRET_VAULT_HXX__
#define __SECRET_VAULT_HXX__

#include "vault_secrets.hpp"

#include <iostream> // cout, cin
#include <fstream> // ofstream, ifstream
#include <ctype.h> // isalpha

static std::string get_file_name()
{
    std::cout << "please enter save name\n";
    std::string file_name;
    bool legal_name = false;
    while(not legal_name)
    {
        legal_name = true;
        std::cin >> file_name;
        for (char const c : file_name)
        {
            if(not isalpha(c))
            {
                std::cout << "you've entered illegal save name, please try again using only alphbetical letters.\n";
                legal_name = false;
                break;
            }
        }
    }
    return file_name;
}

template <typename Secret>
VaultOfSecrets<Secret>::VaultOfSecrets()
: m_secrets{}
, m_file_parser{FileParser<std::string, Secret>::get_instance()}
{
}

// template <typename Secret>
// VaultOfSecrets<Secret>* VaultOfSecrets<Secret>::self_pointer = nullptr;

// template <typename Secret>
// VaultOfSecrets<Secret>* VaultOfSecrets<Secret>::get_instance()
// {
//     if(self_pointer == nullptr)
//     {
//         VaultOfSecrets<Secret>::self_pointer = new VaultOfSecrets();
//     }

//     return VaultOfSecrets<Secret>::self_pointer;
// }

// template <typename Secret>
// VaultOfSecrets<Secret>::~VaultOfSecrets()
// {
//     self_pointer = nullptr;
// }

template <typename Secret>
std::string VaultOfSecrets<Secret>::add(Secret const& a_secret)
{
    std::string key = generate_key();
    m_secrets[key] = a_secret;
    return key;
}

template <typename Secret>
std::string VaultOfSecrets<Secret>::generate_key()
{
    static int counter = 0;
    return "secret" + std::to_string(++counter);
}

template <typename Secret>
Secret const& VaultOfSecrets<Secret>::fetch(std::string const& a_key)
{
    return m_secrets.at(a_key);
}

template <typename Secret>
void VaultOfSecrets<Secret>::save() const
{
    std::string file_name = get_file_name();
    std::ofstream save_file;
    save_file.open(file_name + ".secret", std::ios::trunc);
    m_file_parser->parse_map_into_file(m_secrets, save_file, ",");
    save_file.close();
}

template <typename Secret>
void VaultOfSecrets<Secret>::load()
{
    std::string file_name;
    std::string delimiter = ",";
    std::cout << "please enter save file name to load\n";
    bool legal_name = false;
    while(not legal_name)
    {
        std::cin >> file_name;
        std::ifstream load_file(file_name + ".secret");
        if(load_file.is_open())
        {
            legal_name = true;
            // std::string secret;
            // std::string key;
            // m_secrets.clear();
            // while ( getline (load_file, secret) )
            // {
            //     size_t pos = secret.find(delimiter);
            //     key = secret.substr(0, pos);
            //     secret.erase(0, pos + delimiter.length());
            //     // std::cout << key << ',' << secret << '\n';
            //     m_secrets[key] = std::stod(secret);
            // }
            m_file_parser->parse_file_into_map(m_secrets, load_file, delimiter);
            load_file.close();
        }
        else
        {
            std::cout << "no existing save file with that name, please try again.\n";
        }
    }
    
}

#endif // __SECRET_VAULT_HXX__