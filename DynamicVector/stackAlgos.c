#include "stack.h"
#include <string.h>
#include <stdio.h>

int IsParanthesisBalanced(char* _exp);

int main(void)
{
	char *exp1="{x+(y-[a+b]*c-[(d+e)]}/(h-(j-(k-[l-n]))).", *exp2="if(a+{2*max(A[],5)}>7)", *exp3=" ";
	printf("Let's check if %s Is Paranthesis Balanced! --- ", exp1);
	if(IsParanthesisBalanced(exp1))
	{
		printf("True!\n");
	} else
	{
		printf("False!\n");
	}
	printf("Let's check if %s Is Paranthesis Balanced! --- ", exp2);
	if(IsParanthesisBalanced(exp2))
	{
		printf("True!\n");
	} else
	{
		printf("False!\n");
	}
	printf("Let's check if %s Is Paranthesis Balanced! --- ", exp3);
	if(IsParanthesisBalanced(exp3))
	{
		printf("True!\n");
	} else
	{
		printf("False!\n");
	}
	return 0;
}


int IsParanthesisBalanced(char* _exp)
{
	int i, len = strlen(_exp), lastBracket;
	Stack* stk = StackCreate(len, 0);
	if(!_exp || len < 0 || !stk)
	{
		return FALSE;  
	}
	for(i = 0; i < len; i++)
	{
		if(_exp[i] == '(' || _exp[i] == '[' || _exp[i] == '{')
		{
			StackPush(stk, _exp[i]);
		}
		if(_exp[i] == ')' || _exp[i] == ']' || _exp[i] == '}')
		{
			if(StackIsEmpty(stk))
			{
				return FALSE;
			}
			StackPop(stk, &lastBracket);
			switch (lastBracket)
			{
				case '(':
					if(_exp[i] != ')')
						return FALSE;
					break;
				
				case '[':
					if(_exp[i] != ']')
						return FALSE;
					break;
				
				case '{':
					if(_exp[i] != '}')
						return FALSE;
					break;
			}
		}
	}
	if(!StackIsEmpty(stk))
	{
		return FALSE;
	}
	return TRUE;
}

char* InfixToPostfix(char* _infix)
{
	int len = strlen(infix), i, operator;
	char* postfix = (char*)malloc(sizeof(char) * len);
	char* ptr = postfix;
	Stack* stk = StackCreate(len, 0);
	for(i = 0; i < len; i++)
	{
		if(('0' < _infix[i] && _infix[i] < '9') || ('A' < _infix[i] && _infix[i] < 'z'))
		{
			*(ptr++) = _infix[i];
		}
		else if(_infix[i] == '/' || _infix[i] == '*' || _infix[i] == '-' || _infix[i] == '+')
		{
		
		}
		else if(_infix[i] == '(' || _infix[i] == '[' || _infix[i] == '{')
		{
			StackPush(stk, _infix[i]);
		}
		else if(_infix[i] == ')' || _infix[i] == ']' || _infix[i] == '}')
		{
			while(!StackIsEmpty(stk))
			{
				StackPop(stk, &operator);
				if(operator == '(' || operator == '[' || operator == '{')
				{
					break;
				}
				*(ptr++) = operator;
			}
		}
	}
}

int PostfixCalc(char* _postfix)
{
	int operator, leftOperand, rightOperand
}
