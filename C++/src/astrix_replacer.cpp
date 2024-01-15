#include "astrix_replacer.hpp"

AstrixReplacer::AstrixReplacer()
: m_translator("aeiou", "*****", 5)
{}

void AstrixReplacer::encode(Message const& a_plain, Message& a_cipher)
{
    a_cipher = a_plain;
    std::cout << a_cipher << '\n';
    m_translator.translate(a_cipher);
}