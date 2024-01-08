#ifndef __ADTDEF_H__
#define __ADTDEF_H__

typedef enum
{
/* General ADT Errors */
	ERR_OK = 0,
	ERR_GENERAL,
	ERR_NOT_INITIALIZED,
	ERR_ALLOCATION_FAILED,
	ERR_REALLOCATION_FAILED,
	ERR_UNDERFLOW,
	ERR_OVERFLOW,
	ERR_WRONG_INDEX,
	ERR_EMPTY_LIST,
	ERR_DATA_EXIST,
/* Vector Errors */
/* Stack Errors */
	ERR_STACK_BBBBB = 30
/* LinkedList Errors */
/* Bit Vector*/
} ADTErr;

void HandleErr(ADTErr errNum, char *msg);

#endif /*__ADTDEF_H__*/
