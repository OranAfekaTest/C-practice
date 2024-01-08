#include "AD.h"

Status IncreaseMeetingArray(AD* _ad);
void ShiftMeetingsRight(AD* _ad, int _fromIndex);
void ShiftMeetingsLeft(AD* _ad, Meeting* _meet);


void StatusMsg(Status status);
const char* StatusMessages[] =
{
	"OK",
	"Null Pointer",
	"Illegal Size",
	"Memmory Allocation Failed",
	"Illegal Hour",
	"Time Collision",
	"Meeting Not Found",
	"Name can't be empty",
	"Error while opening file",
	"AD creation failed",
	"Meeting creation failed"
};


AD* CreateAD(int _size, int _blockSize)
{
	AD* ad;
	
	if(!(_size || _blockSize) || _size < 0 || _blockSize < 0)
	{
		return NULL;
	}
	
	ad = (AD*)malloc(sizeof(AD));
	
	if(!ad)
	{
		return NULL;
	}
	
	ad->meetings = (Meeting**)calloc(sizeof(Meeting*), _size);
	
	if(!(ad->meetings))
	{
		free(ad);
		return NULL;
	}
	
	ad->arrSize = _size;
	ad->blockSize = _blockSize;
	ad->numofMeetings = 0;
	
	return ad;
}

Meeting* CreateMeeting(float _beginTime, float _endTime, int _room)
{
	Meeting* meet = NULL;
	if(_beginTime < 0 || _endTime < 0 || _beginTime > 23.99 || _endTime > 23.99 || _endTime < _beginTime)
	{
		return NULL;
	}
	meet = malloc(sizeof(Meeting));
	if(!meet)
	{
		return NULL;
	}
	meet->beginTime = _beginTime;
	meet->endTime = _endTime;
	meet->room = _room;
	return meet;
}

Status InsertMeeting(AD* _ad, Meeting* _meet)
{
	Status status;
	int i;
	if(!_ad || !_meet)
	{
		return NULL_POINTER;
	}
	
	if(_ad->numofMeetings + 1 >= _ad->arrSize) /* allocate more space if needed */
	{
		status = IncreaseMeetingArray(_ad);
		if(status != OK)
		{
			return status;
		}
	}
	for(i = 0; i < _ad->numofMeetings; i++)
	{
		if(_ad->meetings[i]->beginTime < _meet->beginTime)
		{
			if(_ad->meetings[i]->endTime > _meet->beginTime)
			{
				return TIME_COLLISION; /* hour is taken */
			}
			if(!_ad->meetings[i + 1])/* next is empty */
			{
				_ad->meetings[i + 1] = _meet;
				_ad->numofMeetings++;
				return OK;
			}
			if(_meet->endTime < _ad->meetings[i + 1]->beginTime)
			{
				ShiftMeetingsRight(_ad, i + 1);
				_ad->meetings[i + 1] = _meet;
				_ad->numofMeetings++;
				return OK; /* insert new meeting between i and i + 1 */
			} else if(_meet->beginTime < _ad->meetings[i + 1]->beginTime)
			{
				return TIME_COLLISION;
			}
		}
		else if(_ad->meetings[i]->beginTime == _meet->beginTime)
		{
			return TIME_COLLISION; /* hour is taken */
		}
		else if(_meet->endTime < _ad->meetings[i]->beginTime)
		{
			ShiftMeetingsRight(_ad, i);
			_ad->meetings[i] = _meet;
			_ad->numofMeetings++;
			return OK; /* new meet is the first of the day */
		}
		else
		{
			return TIME_COLLISION; /* end time of the insertrd meeting overlaps with begin time of current meeting. */
		}
	}
	if(_ad->numofMeetings == 0)
	{
		_ad->meetings[_ad->numofMeetings] = _meet;
		_ad->numofMeetings++;
		return OK;
	}
}

Status RemoveMeetingByHour(AD* _ad, float _hour)
{
	Meeting* meet = NULL;
	if(!_ad)
	{
		return NULL_POINTER;
	}
	if(_hour < 0 || 24 < _hour)
	{
		return ILLEGAL_HOUR;
	}
	meet = FindMeetingByHour(_ad, _hour);
	if(meet)
	{
		ShiftMeetingsLeft(_ad, meet);
		_ad->numofMeetings--;
		return OK;
	}
	return MEETING_NOT_FOUND;
}

Meeting* FindMeetingByHour(AD* _ad, float _hour)
{
	int i;
	Meeting** meetings;
	if(!_ad || _hour < 0 || 24 < _hour)
	{
		return NULL;
	}
	meetings = _ad->meetings;
	for(i = 0; i < _ad->numofMeetings; i++)
	{
		if(_ad->meetings[i]->beginTime < _hour)
		{
			continue;
		} else if(_ad->meetings[i]->beginTime > _hour)
		{
			return NULL;
		} else
		{
			return _ad->meetings[i];
		}
	}
	return NULL;
}

Status DestroyAD(AD** _ad)
{
	int i;
	if(*_ad)
	{
		if((*_ad)->numofMeetings > 0)
		{
			for(i = 0; i < (*_ad)->numofMeetings; i++)
			{
				free((*_ad)->meetings[i]);
			}
		}
		
		free((*_ad)->meetings);
		free(*_ad);
	}
	*_ad = NULL;
}

Status PrintAD(AD* _ad)
{
	int i;
	if(!_ad)
	{
		return NULL_POINTER;
	}
	printf("You have %d meetings today\n	********\n", _ad->numofMeetings);
	for(i = 0; i < _ad->numofMeetings; i++)
	{
		printf("%2.2f - %2.2f : in room No.%d\n", _ad->meetings[i]->beginTime, _ad->meetings[i]->endTime, _ad->meetings[i]->room);
	}
	printf("	********\nHave a nice day!\n");
	return OK;
}

Status SaveAD(AD* _ad, char* _name)
{
	FILE* file = NULL;
	int i;
	if(!_ad || !_name)
	{
		return NULL_POINTER;
	}
	if(_name == "")
	{
		return ENPTY_NAME;
	}
	file = fopen(_name, "w");
	if(!file)
	{
		return FILE_ERROR;
	}
	fprintf(file, "%d %d\n", _ad->arrSize, _ad->blockSize);
	for(i = 0; i < _ad->numofMeetings; i++)
	{
		fprintf(file, "%f %f %d\n", _ad->meetings[i]->beginTime, _ad->meetings[i]->endTime, _ad->meetings[i]->room);
	}
	fclose(file);
	return OK;
}
Status LoadAD(AD** _ad, char* _name)
{
	FILE* file = NULL;
	Meeting* meet = NULL;
	int i, arrSize, blockSize, room;
	float beginTime, endTime;
	Status status;
	if(!_name)
	{
		return NULL_POINTER;
	}
	if(_name == "")
	{
		return ENPTY_NAME;
	}
	file = fopen(_name, "r");
	if(!file)
	{
		return FILE_ERROR;
	}
	fscanf(file, "%d %d", &arrSize, &blockSize);
	*_ad = CreateAD(arrSize, blockSize);
	if(!*_ad)
	{
		fclose(file);
		return AD_CREATION_FAILED;
	}
	fscanf(file, "%f %f %d", &beginTime, &endTime, &room);
	while(!feof(file))
	{
		meet = CreateMeeting(beginTime, endTime, room);
		if(!meet)
		{
			fclose(file);
			return MEETING_CREATION_FAILED;
		}
		status = InsertMeeting(*_ad, meet);
		if(status != OK)
		{
			fclose(file);
			return status;
		}
		fscanf(file, "%f %f %d", &beginTime, &endTime, &room);
	}
	fclose(file);
	return OK;
}

Status IncreaseMeetingArray(AD* _ad)
{
	Meeting** tmpMeet = NULL;
	int i, size = _ad->arrSize + _ad->blockSize;
	if(_ad->blockSize == 0)
	{
		return ILLIGAL_SIZE;
	}
	tmpMeet = (Meeting**)realloc(_ad->meetings, (sizeof(Meeting*) * size));
	if(!tmpMeet)
	{
		return MEMMORY_ALLOCATION_FAILED;
	}
	for(i = 0; i < _ad->blockSize; i++)
	{
		tmpMeet[_ad->arrSize + i] = NULL;
	}
	_ad->arrSize += _ad->blockSize;
	_ad->meetings = tmpMeet;
	return OK;
}

void ShiftMeetingsRight(AD* _ad, int _fromIndex)
{
	int i;
	for(i = _ad->numofMeetings; i > _fromIndex; i--)
	{
		_ad->meetings[i] = _ad->meetings[i - 1];
	}
	
}

void ShiftMeetingsLeft(AD* _ad, Meeting* _meet)
{
	int i, found = 0;
	for(i = 0; i < _ad->numofMeetings; i++)
	{
		if(_ad->meetings[i] == _meet)
		{
			found = 1;
		}
		if(found)
		{
			_ad->meetings[i] = _ad->meetings[i + 1];
		}
	}
}

void StatusMsg(Status status)
{
	if(status) 
	{
		printf(" Status=%s\n", StatusMessages[status]);
	}

}
