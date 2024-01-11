#include "Status.h"
#include <stdio.h>

const char* StatusDescription[] =
{
	"OK",
	"GENERAL ERROR",
	"NOT INITIALIZED",
	"ALLOCATION FAILED",
	"UNDERFLOW",
	"OVERFLOW",
	"WRONG INDEX",
	"EMPTY DECK",
	"EMPTY HAND"
	"DATA EXIST",

};

void StatusHandler(Status _status, char *msg)
{
    if(_status)
    {
	    printf("%s, %s.\n",StatusDescription[_status], msg);
    }
}