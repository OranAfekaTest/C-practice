#include <stdio.h>
#include <math.h>

int FactorialNumber(int _n);
int Palindrome(int _n);
int AscendingInt(int num);
int ReverseNumber(int _num);

int main(void)
{
	int num;
	num = 4;
	printf("FactorialNumber of %d = %d \n",num, FactorialNumber(num));
	num = 475674;
	printf("is %d a Palindrome %d \n",num, Palindrome(num));
	num = 1324;
	printf("is %d an AscendingInt %d \n",num, AscendingInt(num));

	printf("%d in ReverseNumber is %d \n",num, ReverseNumber(num));

	return 0;
}

int DigitCount(int _num)
{
	int digitNumber = 0;
	while(_num > 0)
	{
		_num /= 10;
		digitNumber++;
	}
	return digitNumber;
}

int FactorialNumber(int _n)
{
	int i, result = 1;
	for(i = 2; i <= _n; i++)
	{
		result *= i;
	}

	return result;
}

int Palindrome(int _n)
{
	int digitNumber, i;
	int leftDigit, rightDigit;
	digitNumber = DigitCount(_n);
	
	while(_n > 9){
		leftDigit = _n / pow(10, digitNumber - 1);
		rightDigit = _n % 10;
		if (leftDigit != rightDigit)
		{
			return 0;
		}
		_n %= (int)pow(10, digitNumber - 1);
		_n /= 10;
		digitNumber -= 2;
	}
	return 1;
}

int AscendingInt(int num)
{
	int digit1, digit2;
	while(num > 9)
	{
		digit1 = num % 10;
		digit2 = (num / 10) % 10;
		if(digit1 < digit2)
		{
			return 0;
		}
		num /= 10;
	}
	return 1;
}

int IsPrime(int _num)
{
	int i;
	if(!_num)
	{
		return 0;
	}
	for(i = 2; i < _num; i++)
	{
		if(_num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int ReverseNumber(int _num)
{
	int result = 0, i;
	int digitNumber = DigitCount(_num);
	for(i = digitNumber - 1; i >= 0; i--)
	{
		result += (_num % 10) * pow(10, i);
		_num /= 10;
		printf("result = %d num = %d \n", result, _num);
	}
	return result;
}
