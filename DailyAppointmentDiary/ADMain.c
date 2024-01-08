#include "AD.h"

int main(void)
{
	int userInput, roomInput;
	float beginTimeInput, endTimeInput;
	char fileName[10];
	Meeting *meet = NULL;
	Status status;
	AD* myAD = CreateAD(ARBITRARY_INITIAL_SIZE, ARBITRARY_INITIAL_SIZE);
	
	
	do
	{
		printf("Walcome to your Daily Appointment Diary!\nWhat would you like to do?\n");
		printf("1. Print my Daily diary\n2. Create a new meeting\n3. Find Meeting By Hour\n4. Remove Meeting By Hour\n5. Save Daily Appointments\n6. Load Daily Appointments\n0. exit\n");
		scanf("%d", &userInput);
		switch (userInput)
		{
			case 0:
				break;
			case 1:
				PrintAD(myAD);
				break;
			case 2:
				printf("\nPlease enter the begin time for meeting:\n");
				scanf("%f", &beginTimeInput);
				printf("Please enter the end time for meeting:\n");
				scanf("%f", &endTimeInput);
				printf("Please enter the room number of the meeting:\n");
				scanf("%d", &roomInput);
				meet = CreateMeeting(beginTimeInput, endTimeInput, roomInput);
				if(!meet)
				{
					printf("\n-Failed to create meeting-\n");
				}
				else
				{
					status = InsertMeeting(myAD, meet);
					if(status != OK)
					{
						printf("\n-Failed to insert meeting-\n");
						StatusMsg(status);
						free(meet);
					}
				}
				break;
			case 3:
				printf("\nPlease enter the begin time for meeting:\n");
				scanf("%f", &beginTimeInput);
				meet = FindMeetingByHour(myAD, beginTimeInput);
				if(!meet)
				{
					printf("\n-Failed to find meeting-\n");
				}
				else
				{
					printf("The meeting is at: %2.2f - %2.2f : in room No.%d\n", meet->beginTime, meet->endTime, meet->room);
				}
				break;
			case 4:
				printf("\nPlease enter the begin time for meeting:\n");
				scanf("%f", &beginTimeInput);
				status = RemoveMeetingByHour(myAD, beginTimeInput);
				if(status != OK)
					{
						printf("\n-Failed to remove meeting-\n");
						StatusMsg(status);
					}
				break;
			case 5:
				printf("\nPlease enter file name save:[10 chars MAX]\n");
				scanf("%s", fileName);
				status = SaveAD(myAD, fileName);
				if(status != OK)
					{
						printf("\n-Failed to save meetings-\n");
						StatusMsg(status);
					}
				break;
			case 6:
				printf("\nPlease enter file name load:[10 chars MAX]\n");
				scanf("%s", fileName);
				status = LoadAD(&myAD, fileName);
				if(status != OK)
					{
						printf("\n-Failed to load meetings-\n");
						StatusMsg(status);
					}
				break;
			default:
				printf("\n-Illegal input, please insert a number between 0 - 4 as shown on the menu.\n");
				break;
		}
			
				
	
	}while(userInput);
	

	DestroyAD(&myAD);
	return 0;
}
