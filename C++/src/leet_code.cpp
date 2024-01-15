#include "leet_code.hpp"

LeetCode::LeetCode()
: m_translator("oizeasgtbr", "0123456789", 10)
{}

void LeetCode::encode(Message const& a_plain, Message& a_cipher)
{
    a_cipher = a_plain;
    std::cout << a_cipher << '\n';
    m_translator.translate(a_cipher);
}