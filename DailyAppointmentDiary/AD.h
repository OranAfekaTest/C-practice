#ifndef __AD_H__
#define __AD_H__
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define ARBITRARY_INITIAL_SIZE 4

enum Status {OK, NULL_POINTER, ILLIGAL_SIZE, MEMMORY_ALLOCATION_FAILED, ILLEGAL_HOUR, TIME_COLLISION, MEETING_NOT_FOUND, ENPTY_NAME, FILE_ERROR, AD_CREATION_FAILED, MEETING_CREATION_FAILED} typedef Status;
void StatusMsg(Status status);

struct Meeting
{
	float beginTime;
	float endTime;
	int room;
}typedef Meeting;

struct AD
{
	int arrSize;
	int blockSize;
	Meeting** meetings;
	int numofMeetings;
}typedef AD;

AD* CreateAD();
Meeting* CreateMeeting(float beginTime, float endTime, int room);
Status InsertMeeting(AD* _ad, Meeting* _meet);
Status RemoveMeetingByHour(AD* _ad, float _hour);
Meeting* FindMeetingByHour(AD* _ad, float _hour);
Status DestroyAD(AD** _ad);
Status PrintAD(AD* _ad);
Status SaveAD(AD* _ad, char* _name);
Status LoadAD(AD** _ad, char* _name);

#endif /*__AD_H__*/
