#include "ui.h"

#define YELLOW "\x1B[33m"
#define NORMAL "\x1B[0m"
#define RED "\x1B[91m"
#define GREEN "\x1B[32m"

int MainMenu(void)
{
	int mainChoice = 0;
	printf(YELLOW);
	printf("\n--------------Main Menu--------------\n\n");
	printf(NORMAL);
	printf("1 - Registration\n");
	printf("2 - Log in\n");
	printf("3 - Exit\n");
	printf( "Select your choice: ");
	scanf("%d", &mainChoice);
	
	return mainChoice;
}

int SecondMenu(void)
{
	int secondChoice = 0;
	printf(YELLOW);
	printf("\n--------------Group Menu--------------\n\n");
	printf(NORMAL);
	printf("1 - Join group\n");
	printf("2 - Leave group \n");
	printf("3 - Create new group\n");
	printf("4 - Log out\n");
	printf("Select your choice: ");
	scanf("%d", &secondChoice);
	return secondChoice + 3;
}

void InsertName(char* _name)
{
	printf("please enter your user name: ");
	scanf("%s", _name);  
}

void InsertPassWord(char* _passWord)
{
	printf("please enter your passWord: ");
	scanf("%s", _passWord);  
}


void InsertGroupName(char* _name)
{
	printf("Please enter group name: ");
	scanf("%s", _name);  
	return;
}

void PrintInvalidChoice(void)
{
	printf(RED);
	printf("\n  ->  ");
	printf("Invalid choice!");
	printf("  <-  \n");
} 

void PrintToClient(ADTResult _type, MenuSwitch _mSwitch)
{	
	switch(_mSwitch)
	{
		case REGISTRATION:
			switch(_type)
			{
				case SUCCESS:
					printf(GREEN);
					printf("\n  ->  ");
					printf("Registration success!");
					printf("  <-  \n");
					break;

				case INVALID_NAME:
					printf(RED);
					printf("\n  ->  ");
					printf("Registration fail. User name taken!");
					printf("  <-  \n");
					break;
				
				case SEND_FAILED:
				case UNINITIALIZED:
				case ALLOCATION_ERROR:
					printf(RED);
					printf("\n  ->  ");
					printf("An error occured, try again!");
					printf("  <-  \n");
					break;
			}
			break;
			
		case LOG_IN:
			switch(_type)
			{
				case SUCCESS:
					printf(GREEN);
					printf("\n  ->  ");
					printf("Log in success!");
					printf("  <-  \n");
					break;
				
				case INVALID_NAME:
					printf(RED);
					printf("\n  ->  ");
					printf("Log in fail. Wrong user name!");
					printf("  <-  \n");
					break;

				case INVALID_PASSWORD:
					printf(RED);
					printf("\n  ->  ");
					printf("Log in fail. Wrong password !");
					printf("  <-  \n");
					break;

				case UNINITIALIZED:/*ALREADY_LOG_IN*/
					printf(RED);
					printf("\n  ->  ");
					printf("Log in fail. Try again !");
					printf("  <-  \n");
					break;

				case LOGGED_IN:/*ALREADY_LOG_IN*/
					printf(RED);
					printf("\n  ->  ");
					printf("You are already logged in!");
					printf("  <-  \n");
					break;

			}
			break;

		case JOIN_GROUP:
			switch(_type)
			{
				case SUCCESS:
					printf(GREEN);
					printf("\n  ->  ");
					printf("successfully connected to the group!");
					printf("  <-  \n");
					break;

				case RECEIVE_FAILED: 
					printf(RED);
					printf("\n  ->  ");
					printf("Join fail. try again!");
					printf("  <-  \n");
					break;

				case INVALID_NAME:/*GROUP_NOT_FOUND*/
					printf(RED);
					printf("\n  ->  ");
					printf("No such group. try again!");
					printf("  <-  \n");
					break;

				case SEND_FAILED:/*DUPLICATE_GROUP_CONNECT*/
					printf(RED);
					printf("\n  ->  ");
					printf("Join fail. try again!");
					printf("  <-  \n");
					break;	
				
				case EMPTY_GROUPS:
					printf(RED);
					printf("\n  ->  ");
					printf("No such group. try again!");
					printf("  <-  \n");
					break;

			}
			break;
		case LEAVE_GROUP:
			switch(_type)
			{
				case SUCCESS:/*LEAVE_GROUP_SUCCESS*/
					printf(GREEN);
					printf("\n  ->  ");
					printf("You left the group successfully!");
					printf("  <-  \n");
					break;
			
				case UNINITIALIZED:/*LEAVE_GROUP_FAIL*/
				case SEND_FAILED:
				case RECEIVE_FAILED:
					printf(RED);
					printf("\n  ->  ");
					printf("Leave fail. try again!");
					printf("  <-  \n");
					break;
					
				case INVALID_NAME:
					printf(YELLOW);
					printf("\n  ->  ");
					printf("You are not logged in to such group");
					printf("  <-  \n");
					break;

			}
			break;
		case CREATE_GROUP:
			switch(_type)
			{
				case INVALID_NAME:/*DUPLICATE_GROUP_NAME*/
					printf(RED);
					printf("\n  ->  ");
					printf("Duplicate group name. choose new name!");
					printf("  <-  \n");
					break;
			
				case SUCCESS:/*OPEN_NEW_GROUP_SUCCESS*/
					printf(GREEN);
					printf("\n  ->  ");
					printf("The group opened successfully!");
					printf("  <-  \n");
					break;	

				case UNINITIALIZED:/*OPEN_NEW_GROUP_FAIL*/
				case SEND_FAILED:
				case RECEIVE_FAILED:
				case ALLOCATION_ERROR:	
					printf(RED);
					printf("\n  ->  ");
					printf("Failed to open the group. try again!");
					printf("  <-  \n");
					break;	

			}
			break;
		case LOG_OUT:
			switch(_type)
			{
				case SUCCESS:/*log out_SUCCESS*/
					printf(GREEN);
					printf("\n  ->  ");
					printf("Successfully log out!");
					printf("  <-  \n");
					break;

				case UNINITIALIZED:/*log out FAILED*/
					printf(GREEN);
					printf("\n  ->  ");
					printf("Failed to log out!");
					printf("  <-  \n");
					break;

			}
			break;
		case EXIT:
			switch(_type)
			{	
				case SUCCESS:/*EXIT SUCCESS*/
					printf(GREEN);
					printf("\n  ->  ");
					printf("EXIT Success :)");
					printf("  <-  \n");
					break;
			}
			break;
	}
			
	
}

void PrintGroupsNames(char* _groups)
{
	char* groupName, i = 2;
	char delim[2] = "\n";
	groupName = strtok( _groups+1, delim );
	puts("Group List:");
	printf("\n1) %s.\n", groupName );
	while( groupName = strtok( NULL, delim ) )
	{
		printf("\n%d) %s.\n", i, groupName );
		++i;
	}
}
