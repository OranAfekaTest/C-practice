#include <stdio.h>
#include <string.h>
#include "strings.h"

void SwapChars(char *_a, char *_b);
int CompareChars(char *_a, char *_b);
char* SkipBlanks(char **_str);
char* CheckSign(char *_str, int *sign);
int CountDigits(int _num);

int Reverse(char *_str)
{
	int strLength;
	char *leftPtr = NULL, *rightPtr = NULL;
	
	if(_str == NULL)
	{
		return NULL_POINTER_EXCEPTION;
	}
	
	strLength = strlen(_str);
	leftPtr = _str, rightPtr = &_str[strLength-1];
	
	while(leftPtr < rightPtr)
	{
		SwapChars(leftPtr,rightPtr);
		++leftPtr;
		--rightPtr;
	}

	return OK;
}

int IsPalindrome(char *_str, int *status)
{
	int strLength;
	char *leftPtr, *rightPtr;
	*status = (_str == NULL ? NULL_POINTER_EXCEPTION : OK);
	strLength = strlen(_str);
	leftPtr = _str, rightPtr = &_str[strLength-1];
	while(leftPtr < rightPtr)
	{
		if(!CompareChars(leftPtr,rightPtr))
		{
			return FALSE;
		}
		++leftPtr;
		--rightPtr;
	}
	
	return TRUE;
	
}

int MyAToI(char *_str, int *status)
{
	int result = 0 , i = 0, sign;
	*status =(_str == NULL ? NULL_POINTER_EXCEPTION : OK);
	SkipBlanks(&_str);
	_str = CheckSign(_str, &sign);
	do
	{
		result += (_str[i] - '0');
		i++;
		if(_str[i] != '\0')
			result *= 10;
		
	}while(_str[i] != '\0' && isdigit(_str[i]));
	
	return sign * result;
}

int MyIToA(char *str, int _num)
{
	int currentDigit, numofDigits, i;
	numofDigits = CountDigits(_num);
	str[numofDigits] = '\0';
	for(i = numofDigits - 1; i >= 0; i--)
	{
		str[i] = _num % 10 + '0';
		_num /= 10;
	}
	return OK;
}

void SwapChars(char *_a, char *_b)
{
	char temp = *_a;
	*_a = *_b;
	*_b = temp;
}

int CompareChars(char *_a, char *_b)
{
	if (*_a == *_b)
		return TRUE;
	else
		return FALSE;
}

char* SkipBlanks(char **_str)
{
	while(**_str == ' ')
		(*_str)++;

}

char* CheckSign(char *_str, int *sign)
{
	if(*_str == '-')
	{
		_str++;
		*sign = -1;
	}
	else if(*_str == '+')
	{
		_str++;
		*sign = 1;
	}
	else if(isdigit(*_str))
	{
		*sign = TRUE;
	}
	else
	{
		*sign = FALSE;
	}
	
	return _str;
}

int CountDigits(int _num)
{
	int result = 0;
	while(_num > 0)
	{
		_num /= 10;
		result++;
	}
	return result;
}

