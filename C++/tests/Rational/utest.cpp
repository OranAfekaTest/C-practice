#include "mu_test.h"
#include "rational.hpp"

#include <cstdio>

using namespace algebra;

BEGIN_TEST(equality_on_mul_and_div)
	Rational ten(20, 2);
    Rational quarter(1, 4);
    Rational two_and_a_half(5, 2);

	ASSERT_THAT(ten * quarter == two_and_a_half);
	// ASSERT_EQUAL(two_and_a_half / quarter, ten);
	// ASSERT_EQUAL(ten / two_and_a_half, quarter.inverse());

END_TEST
/*
void test(Rational a_fraction)
{
    printf("Testing: ");
    a_fraction.print();
    printf("  which really is a %f\n", a_fraction.value());
}

void testAdd(Rational a_fraction, Rational a_test)
{
    printf("Adding ");
    a_test.print();
    printf(" to ");
    a_fraction.print();
    a_fraction + (a_test);
    printf(" equals: ");

    a_fraction.print();
    puts("");
}

void testMul(Rational a_fraction, Rational a_test)
{
    printf("Multiplying ");
    a_fraction.print();
    printf(" by ");
    a_test.print();
    a_fraction * (a_test);
    printf(" equals: ");

    a_fraction.print();
    puts("");
}

void testDiv(Rational a_fraction, Rational a_test)
{
    printf("Dividing ");
    a_fraction.print();
    printf(" by ");
    a_test.print();
    a_fraction / (a_test);
    printf(" equals: ");

    a_fraction.print();
    puts("");
}

void testSub(Rational a_fraction, Rational a_test)
{
    printf("Dividing ");
    a_fraction.print();
    printf(" by ");
    a_test.print();
    a_fraction - (a_test);
    printf(" equals: ");

    a_fraction.print();
    puts("");
}

void testAddTo(Rational a_fraction, Rational a_test)
{

}

void testSubFrom(Rational a_fraction, Rational a_test)
{

}

void testMulWith(Rational a_fraction, Rational a_test)
{

}

void testDivBy(Rational a_fraction, Rational a_test)
{

}

int main()
{
    Rational ten(20, 2);
    test(ten);

    Rational quarter(1, 4);
    test(quarter);

    Rational two_and_a_half(5, 2);
    test(two_and_a_half);

    testAdd(quarter, two_and_a_half);
    testSub(ten, quarter);
    testMul(two_and_a_half, quarter);
    testDiv(ten, two_and_a_half);
    testAddTo(quarter, two_and_a_half);
    testSubFrom(ten, quarter);
    testMulWith(two_and_a_half, quarter);
    testDivBy(ten, two_and_a_half);

}
*/
TEST_SUITE(always salt your pasta before boiling it)
	
	TEST(equality_on_mul_and_div)
	//IGNORE_TEST(equality_on_mul_and_div)

END_SUITE
