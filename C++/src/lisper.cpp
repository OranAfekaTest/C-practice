#include "lisper.hpp"

#include <locale> // isalnum
#include <map>
namespace encryptions
{
Lisper::Lisper(std::string a_key)
: m_key(a_key)
{}

static size_t get_message_length(Message const& a_message)
{
    size_t result = 0;
    auto itr = a_message.begin();
    auto end = a_message.end();
    while(itr != end)
    {
        if(isalnum(*itr))
        {
            ++result;
        }
        ++itr;
    }
    return result;
}

static char** make_matrix(size_t a_row, size_t a_col, Message const& a_message)
{
    char** result = new char*[a_row];
    for (size_t i = 0; i < a_row; i++)
    {
        result[i] = new char[a_col]{'*'};
    }
    
    auto itr = a_message.begin();
    auto end = a_message.end();

    for (size_t i = 0; i < a_row and itr != end; ++i)
    {
        for (size_t j = 0; j < a_col and itr != end; ++itr)
        {
            if(isalnum(*itr))
            {
                result[i][j] = *itr;
                ++j;
            }
        }
    }

    return result;
}

static void encrypt_cipher(Message& a_message, std::map<char, size_t> const& a_key_order, char*const* a_matrix, size_t a_row)
{
    auto cipher_itr = a_message.begin();
    auto cipher_end = a_message.end();
    for (auto const& key_letter : a_key_order)
    {
        size_t j = key_letter.second;
        for (size_t i = 0; i < a_row; i++)
        {
            if(cipher_itr != cipher_end)
            {
                *cipher_itr = a_matrix[i][j];
                ++cipher_itr;
                std::cout << "encrypt_cipher: " << a_message << '\n';
            } else {
                break;
            } 
        }
    }

    while(cipher_itr != cipher_end)
    {
        *cipher_itr = '*';
        ++cipher_itr;
    }
}

static void free_matrix(char** a_matrix, size_t a_row)
{
    for (size_t i = 0; i < a_row; i++)
    {
        delete a_matrix[i];
    }
    delete a_matrix;
}

static void set_key_order(std::map<char, size_t>& a_key_map, std::string a_key)
{
    for (size_t i = 0; i < a_key.length(); i++)
    {
        a_key_map[a_key[i]] = i;
    }
}

void Lisper::encode(Message const& a_plain, Message& a_cipher)
{
    a_cipher = a_plain; // text allocation

    size_t len = get_message_length(a_plain);
    size_t col = m_key.length();
    
    if(!len or !col)
    {
        return;
    }
    size_t row = len/col;
    if(len % col)
    {
        ++row;
    }

    std::map<char, size_t> key_order;
    set_key_order(key_order, m_key);
    
    char** matrix = make_matrix(row, col, a_plain);
    
    encrypt_cipher(a_cipher, key_order, matrix, row);

    free_matrix(matrix, row);

}
} //encryptions