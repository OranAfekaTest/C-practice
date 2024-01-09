#include "strings.h"
#include <stdio.h>

int main(void)
{
	int status, myInt = 435;
	char str[] = "Hellow World", pal[] =  "203747332" , atoi[] = "    -564", itoa[10];
	Reverse(str);
	printf("%s\n",str);
	if(IsPalindrome(pal, &status))
	{
		printf("%s Is a Palindrome\n",pal);
	}
	else
	{
		printf("%s Isn't a Palindrome\n",pal);
	}

	printf("8 + my string = %d\n", 8 + MyAToI(atoi, &status));
	
	MyIToA(itoa, myInt);
	printf("my Int was: %d and as string: %s \n", myInt, itoa);
	return 0;
}
