#ifndef __STATUS_H__
#define __STATUS_H__

typedef enum Status
{
	OK = 0,
	GENERAL,
	NOT_INITIALIZED,
	ALLOCATION_FAILED,
	UNDERFLOW,
	OVERFLOW,
	WRONG_INDEX,
	EMPTY_DECK,
	EMPTY_HAND,
	DATA_EXIST
} Status;

void StatusHandler(Status _status, char *msg);

#endif /* __STATUS_H__ */