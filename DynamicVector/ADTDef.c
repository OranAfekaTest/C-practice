#include "ADTDef.h"
#include <stdio.h>

const char* ErrDescription[] =
{
/* General ADT Errors - Description */
	"OK",
	"General Error",
	"Initialization error",
	"Allocation error",
	"ReAllocation error",
	"Underflow error",
	"Overflow error",
	"Wrong index",
	"List is empty",
	"Data already exists"
/* Vector Errors */
/* Stack Errors */
/* LinkedList Errors */
/* Bit Vector*/
};

void HandleErr(ADTErr errNum, char *msg)
{
	if(errNum) 
	{
		printf("ErrNum=%d, ErrDescription=%s, msg=%s\n",
		errNum, ErrDescription[errNum],msg);
	}

}
