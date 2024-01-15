#include "mu_test.h"
#include "smart_ptr.hpp"

#include <iostream> // cout

class Test
{
public:
	void shoot(){std::cout << "->pyu!\n";}
	int get(){return 42;}
};

BEGIN_TEST(default_ctor_creates_nullptr)
	int* p = nullptr;
	SmartPointer<int> sp;

	ASSERT_EQUAL(sp.get(), p);

END_TEST

BEGIN_TEST(using_arrow)
	
    Test test;
	Test* test_ptr = &test;
	SmartPointer sp{new Test};
    test_ptr->shoot();
	sp->shoot();
	int first = test_ptr->get();
	int second = sp->get();
	ASSERT_EQUAL(first, second);

END_TEST

BEGIN_TEST(using_astrix)
	Test test;
	Test* test_ptr = &test;
	SmartPointer sp{new Test};
    (*test_ptr).shoot();
	(*sp).shoot();
	int first = (*test_ptr).get();
	int second = (*sp).get();
	ASSERT_EQUAL(first, second);
END_TEST

BEGIN_TEST(using_bool)
	SmartPointer<Test> first;
	SmartPointer second{new Test};

	ASSERT_THAT(not first);
	ASSERT_THAT(second);

END_TEST

TEST_SUITE(lorem ipsum)
	
	TEST(default_ctor_creates_nullptr)
	TEST(using_arrow)
	TEST(using_astrix)
	TEST(using_bool)

END_SUITE
