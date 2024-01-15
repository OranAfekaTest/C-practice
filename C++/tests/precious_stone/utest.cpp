#include "mu_test.h"
#include "text_message.hpp"
#include "uppercase.hpp"
#include "astrix_replacer.hpp"
#include "leet_code.hpp"
#include "caesar_encryption.hpp"
#include "rot13.hpp"
#include "lisper.hpp"
#include "scytale.hpp"
#include "console_destination.hpp"
#include "console_source.hpp"
#include "precious_stone.hpp"

using namespace encryptions;

BEGIN_TEST(uppercase)
	
    TextMessage plain("code like shit");
    TextMessage cipher;
    
    Uppercase upper;
    upper.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "CODE LIKE SHIT");
    
END_TEST

BEGIN_TEST(astrix_replacer)
	
    TextMessage plain("code like shit");
    TextMessage cipher;
    
    AstrixReplacer ar;
    ar.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "c*d* l*k* sh*t");

END_TEST

BEGIN_TEST(leet_code)
	
    TextMessage plain("code like shit");
    TextMessage cipher;
    
    LeetCode leet;
    leet.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "c0d3 l1k3 5h17");

END_TEST

BEGIN_TEST(caesar_encryption)
	
    TextMessage plain("code like shit");
    TextMessage cipher;
    
    CaesarEncryption caeser(7);
    caeser.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "jvkl sprl zopa");

    CaesarEncryption caeser13(13);
    caeser13.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "pbqr yvxr fuvg");

END_TEST

BEGIN_TEST(rot13)
	
    TextMessage plain("code like shit");
    TextMessage cipher;
    
    Rot13 r13;
    r13.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "pbqr yvxr fuvg");

END_TEST

BEGIN_TEST(lisper)
	
    TextMessage plain("code like shit");
    TextMessage cipher;

    Lisper lsp("lisper");
    lsp.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "lioeckehitds**");

    Lisper lsp7("abcde");
    lsp7.encode(plain, cipher);
    std::cout << "cipher: " << cipher << "\n";
	ASSERT_THAT(cipher == "ceosdheiltik**");

END_TEST

BEGIN_TEST(scytale)
	
    TextMessage plain("code like shit");
    TextMessage cipher;

    Scytale scytale(7);
    scytale.encode(plain, cipher);
    TRACE("cipher");
	ASSERT_THAT(cipher == "ceosdheiltik**");

END_TEST

BEGIN_TEST(console_destination)
	
    TextMessage message("console_destination: code like shit\n");

    ConsoleDestination cd;
    cd.send(message);
	ASSERT_EQUAL_STR("console_destination", "console_destination");

END_TEST

BEGIN_TEST(console_source)
	
    TextMessage copy;
    ConsoleSource cs;

    Message* message = cs.receive();
    copy = *message;
	ASSERT_THAT(copy == "code like shit");

END_TEST

BEGIN_TEST(uppercase_precious_stone_console_to_console)
	
    ConsoleSource cs;
    ConsoleDestination cd;
    Uppercase upper;
    TextMessage message("code like shit");
    PreciousStone palantir(cs,cd, upper);
    palantir.execute();
	ASSERT_EQUAL(message, "code like shit");

END_TEST

TEST_SUITE(always salt your pasta while boiling it)
	
	TEST(uppercase)
    TEST(astrix_replacer)
    TEST(leet_code)
    TEST(caesar_encryption)
    TEST(rot13)
    TEST(lisper)
    TEST(scytale)
    TEST(console_destination)
    TEST(console_source)
    TEST(uppercase_precious_stone_console_to_console)

END_SUITE
