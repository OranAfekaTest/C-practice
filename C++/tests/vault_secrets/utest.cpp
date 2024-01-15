#include "mu_test.h"
#include "vault_secrets.hpp"

#include <iostream> // cout

BEGIN_TEST(singleton_craete)
	auto vault1 = VaultOfSecrets<double>::get_instance();
	auto vault2 = VaultOfSecrets<double>::get_instance();

	ASSERT_EQUAL(vault1, vault2);

END_TEST

BEGIN_TEST(add_and_fetch)
	auto vault = VaultOfSecrets<double>::get_instance();

	double pi = 3.1415;
	std::string pi_key = vault->add(pi);
	double bring_me_pi = vault->fetch(pi_key);

	ASSERT_EQUAL(bring_me_pi, pi);

END_TEST

BEGIN_TEST(save)
	auto vault = VaultOfSecrets<double>::get_instance();

	double pi = 3.1415;
	std::string pi_key = vault->add(pi);
	vault->add(pi + 1);
	vault->add(pi + 2);
	vault->add(pi + 3);
	vault->add(pi + 4);
	vault->save();
	

	ASSERT_PASS();

END_TEST

BEGIN_TEST(load)
	auto vault = VaultOfSecrets<double>::get_instance();

	vault->load();
	for(int i = 2; i < 7; i++)
	{
		std::cout << i << ' ';
		std::cout << vault->fetch("secret" + std::to_string(i)) << '\n';
	}
	

	ASSERT_PASS();

END_TEST

TEST_SUITE(lorem ipsum)
	
	TEST(singleton_craete)
	TEST(add_and_fetch)
	TEST(save)
	TEST(load)

END_SUITE
