#include <string.h>
#include "stringHW.h"

void ShiftLeft(char* s1);

int Squeeze(char* s1, char* s2)
{
	int i, j, s1Length, s2Length;
	if(s1 == NULL || s2 == NULL)
		return NULL_POINTER_EXCEPTION;
	s1Length = strlen(s1);
	s2Length = strlen(s2);
	
	for(i = 0; i < s1Length; i++)
	{
		for(j = 0; j < s2Length; j++)
		{
			if(s1[i] == s2[j])
			{
				ShiftLeft(&s1[i]);
			}
			
		}
	}
	return OK;
}

int Location(char* s1, char* s2)
{
	int i, j, s1Length, s2Length, flag = 0;
	if(s1 == NULL || s2 == NULL)
		return LOCATION_ERROR;
	s1Length = strlen(s1);
	s2Length = strlen(s2);
	
	for(i = 0; i < s1Length; i++)
	{
		for(j = 0; j < s2Length; j++)
		{
			if(s1[i] != s2[j])
			{
				flag = 0;
				break;
			}
			else
			{
				i++;
				flag = 1;
			}
		}
		if(flag)
		{
			return i;
		}
	}
	return LOCATION_ERROR;
}

int STrim(char* str)
{
	if(str == NULL)
		return NULL_POINTER_EXCEPTION;
	
	while(*str != '\0')
	{
		if(*str == ' ' && *(str + 1) == ' ')
		{
			ShiftLeft(str + 1);
		}
		else
		{
			str++;
		}
	}
	
	return OK;
}

void ShiftLeft(char* s1)
{
	while(*(s1 + 1) != '\0')
	{
		*s1 = *(s1 + 1);
		s1++;
	}
	*s1 = '\0';
}
