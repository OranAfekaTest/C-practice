#include "ClientManager.h"
#include "ClientNet.h"
#include "ui.h"
#include "TLVProtocol.h"
#include <stdio.h>
#include <string.h>
#include "../../Generics/List/listFunctions.h"
#include <unistd.h>
#include <signal.h> /* kill */
#include <sys/types.h> /* pid_t */

struct ClientManager
{
	ClientNet* m_clientNet ;
	char* m_loggedUser;
	List* m_groupsPIDS;
};

typedef struct GroupInfo
{
	char m_groupName[MAX_NAME_LENGTH];
	pid_t m_sendPID;
	pid_t m_recvPID;
}GroupInfo;

static void ClearSet(char* _name , char* _password , char* _buffer , char*  _answer);
static int LogInCase(ClientManager* _client, char* _buffer);
static int RunChat(char* _ip, int _port, char* _usrName, char* _groupName, List* _pids);
static int IsGroupFound( void* _groupInfo, void* _gNameCheck );
static int LeaveGroup( ClientManager* _client, char* _gName );
static void CloseGroupWindows( ClientManager* _client, char* _gName );
static int PrintGroups( ClientManager* _client, char* _buffer );

ClientManager* CreateClientManager()
{
	ClientManager* cManager = NULL;
	ClientNet* clientNet;
	cManager = (ClientManager*)malloc(sizeof(ClientManager));
	if(!cManager)
	{
		return NULL;
	}
	
	clientNet = createClient();
	if(!clientNet)
	{
		free(cManager);
		return NULL;
	}
	
	if((cManager->m_groupsPIDS = ListCreate()) == NULL)
	{
		ClientNetDestroy(cManager->m_clientNet);
		free(cManager);
		return NULL;
	}

	cManager->m_clientNet = clientNet;
	cManager->m_loggedUser = NULL;

	return cManager;
}

void DestroyClientManager(ClientManager** _manager)
{
	if(!_manager || !*_manager)
	{
		return;
	}
	ClientNetDestroy( ( *_manager )->m_clientNet);
	ListDestroy( &( *_manager )->m_groupsPIDS, free );
	free(_manager);
	*_manager = NULL;
}


int RunClientManager(ClientManager* _client )
{

	int run = ON ;
	MenuSwitch choice;
	ADTResult result;
	char name[MAX_NAME_LENGTH] , password[MAX_NAME_LENGTH] , buffer[BUFFER_SIZE] , answer;
	size_t packSize;
	choice = MainMenu();
	while( run == ON )
	{
		ClearSet(name, password, buffer, &answer);
		switch(choice)
	  	{
			case REGISTRATION:
				InsertName(name);
				InsertPassWord(password);

				packSize = Pack(buffer , name , password ,TLV_REG_REQ);
				if(Send(_client->m_clientNet , buffer , packSize) == FAIL)
				{
					result = SEND_FAILED;
					PrintToClient(result, REGISTRATION);
					break;
				}		

		 		if(Receive(_client->m_clientNet , buffer , BUFFER_SIZE) == FAIL)
		 		{
		 			result = RECEIVE_FAILED;
					PrintToClient(result, REGISTRATION);
					break;
		 		}

		 		if(Unpack(buffer , &answer , NULL) == TLV_RPLY)
		 		{
		 			result = (ADTResult)answer;
					PrintToClient(result, REGISTRATION);
		 		}
				
				choice = MainMenu();
				continue;
				
			case LOG_IN:
				InsertName(name);
				InsertPassWord(password);
				
				packSize = Pack(buffer , name , password ,TLV_LOG_REQ);
				if(Send(_client->m_clientNet , buffer , packSize) == FAIL)
				{
					result = SEND_FAILED;
					PrintToClient(result, LOG_IN);
					break;
				}

		 		if(Receive(_client->m_clientNet , buffer , BUFFER_SIZE) == FAIL)
		 		{
		 			result = RECEIVE_FAILED;
					PrintToClient(result, LOG_IN);
					break;
		 		}

		 		if(Unpack(buffer , &answer , NULL) == TLV_RPLY)
		 		{
					result = (ADTResult)answer;
					PrintToClient(result, LOG_IN);
					if( result != SUCCESS)
					{
						choice = MainMenu();
						continue;
					}
					else
					{
						_client->m_loggedUser = name;
						choice = LogInCase(_client, buffer);
					}
		 		}
				
				continue;
				
			case EXIT:
				return OFF;
				break;
				
			default:
				choice = MainMenu();
				break;
		}
	}
	return result;
}	

static int LogInCase(ClientManager* _client, char* _buffer)
{
	MenuSwitch secondChoice = 0;
	ADTResult result;
	size_t packSize;
	char groupName[MAX_NAME_LENGTH], answer ,port[sizeof(int) + 1] , ip[IP_LEN], log = ON;
	if(!_client->m_loggedUser)
	{
		return MainMenu();
	}
	while( log == ON )
	{	
		secondChoice = SecondMenu();
		switch(secondChoice)
		{
			case JOIN_GROUP:
				if( PrintGroups( _client, _buffer ) == FAIL )
				{
					break;
				}

				InsertGroupName(groupName);/*by #*/
				packSize = Pack(_buffer , groupName , _client->m_loggedUser ,TLV_JOIN_GROUP);

				if(Send(_client->m_clientNet , _buffer , packSize) == FAIL)
				{
					result = SEND_FAILED;
					PrintToClient(result, JOIN_GROUP);
					break;
				}		

				if(Receive(_client->m_clientNet , _buffer , BUFFER_SIZE) == FAIL)
				{
					result = RECEIVE_FAILED;
					PrintToClient(result, JOIN_GROUP);
					break;
				}

				if(Unpack(_buffer , ip , port) == TLV_GROUP_ADD)
					{
						RunChat(ip, atoi(port), _client->m_loggedUser, groupName, _client->m_groupsPIDS);
					}
					else
					{
						result = (ADTResult)ip;
						PrintToClient(result, JOIN_GROUP);
					}
				break;
				
			case LEAVE_GROUP:
				/*should print list of gorups*/
				InsertGroupName(groupName);
				packSize = Pack(_buffer , groupName , _client->m_loggedUser ,TLV_LEAVE_GROUP);

				if(Send(_client->m_clientNet , _buffer , packSize) == FAIL)
				{
					result = SEND_FAILED;
					
				}		

				if(Receive(_client->m_clientNet , _buffer , BUFFER_SIZE) == FAIL)
				{
					result = RECEIVE_FAILED;
					
				}

				if(Unpack(_buffer , &answer , NULL) == TLV_LEAVE_GROUP)
				{
					result = (ADTResult)answer;
				}

				if(result == SUCCESS)
				{
					CloseGroupWindows( _client, groupName ); 
				}
				PrintToClient(result, LEAVE_GROUP);
				break;
				
			case CREATE_GROUP:
				InsertGroupName(groupName);
				packSize = Pack(_buffer , groupName , _client->m_loggedUser ,TLV_CREATE_GROUP);

				if(Send(_client->m_clientNet , _buffer , packSize) == FAIL)
				{
					result = SEND_FAILED;
					PrintToClient(result, CREATE_GROUP);
					break;
				}		

				if(Receive(_client->m_clientNet , _buffer , BUFFER_SIZE) == FAIL)
				{
					result = RECEIVE_FAILED;
					PrintToClient(result, CREATE_GROUP);
					break;
				}

				if(Unpack(_buffer , ip , port) == TLV_GROUP_ADD)
				{
					RunChat(ip, atoi(port), _client->m_loggedUser, groupName, _client->m_groupsPIDS);
				}
				else
				{
					PrintToClient(result, CREATE_GROUP);
				}
				
				break;

			case LOG_OUT :
				packSize = Pack(_buffer , _client->m_loggedUser, NULL ,TLV_LOG_OUT);
				if(Send(_client->m_clientNet , _buffer , packSize) == FAIL)
				{
					result = SEND_FAILED;
					PrintToClient(result, LOG_OUT);
					break;
				}

		 		if(Receive(_client->m_clientNet , _buffer , BUFFER_SIZE) == FAIL)
		 		{
		 			result = RECEIVE_FAILED;
					PrintToClient(result, LOG_OUT);
					break;
		 		}

		 		if(Unpack(_buffer , &answer , NULL) == TLV_RPLY)
		 		{
					result = (ADTResult)answer;
					PrintToClient(result, LOG_OUT);
					if( result != SUCCESS)
					{
						secondChoice = SecondMenu();
						break;
					}
					else
					{
						log = OFF;
					}
		 		}
				break;
				
			default:
				/*PrintInvalidChoice();*/
				secondChoice = SecondMenu();
				break;
		
		}
	}

}

static void ClearSet(char* _name , char* _password , char* _buffer , char*  _answer)
{
	memset(_name , 0 , MAX_NAME_LENGTH);
	memset(_password , 0 , MAX_NAME_LENGTH);
	memset(_buffer , 0 , BUFFER_SIZE);
	memset(_answer , 0 , 1);
}

static int RunChat(char* _ip, int _port, char* _usrName, char* _groupName, List* _pids)
{
	FILE* fp;
	GroupInfo* group;
	char sendTitle[MAX_NAME_LENGTH], receiveTitle[MAX_NAME_LENGTH];
	char sendCommand[BUFFER_SIZE], recvCommand[BUFFER_SIZE];
	if( ( group = (GroupInfo*) malloc( sizeof( GroupInfo ) ) ) == NULL )
	{
		return FAIL;
	}
	strcpy( group->m_groupName, _groupName );
	sprintf( sendTitle, "%s-%s-Write", _groupName, _usrName);
	sprintf( receiveTitle, "%s-%s-Read", _groupName, _usrName);
	sprintf( sendCommand, "gnome-terminal --title=%s --geometry=50x10+0+0 -- bash -c \"./Send.out %s %d %s; bash\"", sendTitle, _ip, _port, _usrName);
	sprintf( recvCommand, "gnome-terminal --title=%s --geometry=50x15+0+0 -- bash -c \"./Receive.out %s %d; bash\"", receiveTitle, _ip, _port);	
	system(sendCommand);
	system(recvCommand);
	fp = fopen(SEND_PID_FILE, "r" );
	if( fp == NULL )
	{
		perror("Error opening file");
		return FAIL;
	}
	fscanf(fp, "%d", &group->m_sendPID);
	fclose ( fp );
	fp = fopen(RECEIVE_PID_FILE, "r" );
	if( fp == NULL )
	{
		perror("Error opening file");
		return FAIL;
	}
	fscanf(fp, "%d", &group->m_recvPID);
	ListPushHead( _pids, group );
	return TRUE;
}

static int PrintGroups( ClientManager* _client, char* _buffer )
{
	size_t packSize;
	char groupsNames[BUFFER_SIZE];

	packSize = Pack(_buffer , _client->m_loggedUser , NULL  ,TLV_GROUP_LIST);
	if(Send(_client->m_clientNet , _buffer , packSize) == FAIL)
	{
		PrintToClient(SEND_FAILED, JOIN_GROUP);
		return FAIL;
	}

	if(Receive(_client->m_clientNet , _buffer , BUFFER_SIZE) == FAIL)
	{
		PrintToClient(RECEIVE_FAILED, JOIN_GROUP);
		return FAIL;
	}

	if(Unpack(_buffer , groupsNames , NULL) == TLV_RPLY)
	{
		PrintToClient(EMPTY_GROUPS, JOIN_GROUP);
		return FAIL;
	}
	
	PrintGroupsNames( groupsNames );
	return SUCCESS;
}

static void CloseGroupWindows( ClientManager* _client, char* _gName )
{
	ListItr groupInfoNode, begin, end;
	GroupInfo* groupInfo;
	begin = ListItrBegin( _client->m_groupsPIDS );
	end = ListItrEnd( _client->m_groupsPIDS );
	if( ( groupInfoNode = ListItrFindFirst(begin, end, IsGroupFound, _gName ) ) == end )
	{
		return;
	}
	groupInfo = ListItrGet( groupInfoNode );
	kill( ( (GroupInfo*)groupInfo )-> m_sendPID, SIGTERM );
	kill( ( (GroupInfo*)groupInfo )-> m_recvPID, SIGTERM );
	ListItrRemove( groupInfoNode );
	return;
}

static int IsGroupFound( void* _groupInfo, void* _gNameCheck )
{
	return !strcmp( ( (GroupInfo*)_groupInfo )->m_groupName , (char*)_gNameCheck);
}








