#include "ServerManager.h"
#include "serverNet.h"
#include "TLVProtocol.h"
#include "UserManager.h"
#include "GroupManager.h"
#include "../../Generics/Queue/genQueue.h"

struct ServerManager
{
    Server* m_server;
    UserManager* m_users;
    GroupManager* m_groups;
    Queue* m_ipPool;
};

static int NewMessage(Server* _server, int _clientSocket , void* _buffer , size_t _msgSize , void* _context); 
static int NewClient(int _clientSocket); 
static int CloseClient(int _clientSocket); 
static void Fail(Server* _server, int _clientSocket, void* _buffer, void* context); 
static void Registration(ServerManager* _sMan, int _clientSocket, char* _usrName, char* _pass);
static void LogIn(ServerManager* _sMan, int _clientSocket, char* _usrName, char* _pass);
static void JoinGroup(ServerManager* _sMan, int _clientSocket, char* _gName, char* _usrName);
static void LeaveGroup(ServerManager* _sMan, int _clientSocket, char* _gName, char* _usrName);
static void CreateNewGroup(ServerManager* _sMan, int _clientSocket, char* _gName, char* _usrName);
static void GetGroupList(ServerManager* _sMan, int _clientSocket, char* _usrName);
static void LogOut(ServerManager* _sMan, int _clientSocket, char* _usrName);
static Queue* CreateIpPool(void);

ServerManager* CreateServerManager(void)
{
    ServerManager* sMan = NULL;
    sMan = malloc(sizeof(ServerManager));
    if(!sMan)
    {
        puts("allocation fault at CreateServerManager");
        return NULL;
    }
    sMan->m_server = CreateServerNet(SERVER_PORT, NewMessage, NewClient, CloseClient, Fail, (void*)sMan);
    if(!sMan->m_server)
    {
        puts("failed to create serverNet");
        free(sMan);
        return NULL;
    }
    sMan->m_users = CreateUserManager(BACK_LOG);
    if(!sMan->m_users)
    {
        puts("failed to create UserManager");
        DestroyServerNet(&sMan->m_server);
        free(sMan);
        return NULL;
    }
    sMan->m_groups = CreateGroupManager(MAX_GROUPS, CHAT_PORT);
    if(!sMan->m_groups)
    {
        puts("failed to create GroupManagerr");
        DestroyServerNet(&sMan->m_server);
        DestroyUserManager(&sMan->m_users);
        free(sMan);
        return NULL;
    }
    sMan->m_ipPool = CreateIpPool();
    if(!sMan->m_ipPool)
    {
        puts("failed to create IpPool");
        DestroyGroupManager(&sMan->m_groups);
        DestroyServerNet(&sMan->m_server);
        DestroyUserManager(&sMan->m_users);
        free(sMan);
        return NULL;
    }
    return sMan;
}

void RunServer(ServerManager* _sMan)
{
    RunServerNet(_sMan->m_server);
}

void DestroyServerManager(ServerManager** _sMan)
{
    if(_sMan)
    {
        if(*_sMan)
        {
            DestroyServerNet(&(*_sMan)->m_server);
            DestroyUserManager(&(*_sMan)->m_users);
            DestroyGroupManager(&(*_sMan)->m_groups);
            QueueDestroy(&(*_sMan)->m_ipPool, free);
            free(*_sMan);
            *_sMan = NULL;
        }
    }
}

static int NewMessage(Server* _server, int _clientSocket , void* _buffer , size_t _msgSize , void* _context)
{
    char name[MAX_NAME_LENGTH];
    char pass[MAX_NAME_LENGTH];
    ServerManager* sMan = NULL;
    if(!_server || !_buffer || !_msgSize || !_context || _clientSocket < 0)
    {
        printf("error on NewMessage from %d", _clientSocket);
        return FAIL;
    }
    sMan = (ServerManager*)_context;
    switch (Unpack(_buffer, name, pass))
    {
    case TLV_REG_REQ:
        Registration(sMan, _clientSocket, name, pass);
        break;
    
    case TLV_LOG_REQ:
        LogIn(sMan, _clientSocket, name, pass);
        break;
    
    case TLV_JOIN_GROUP:
        JoinGroup(sMan, _clientSocket, name, pass);
        break;
    
    case TLV_LEAVE_GROUP:
        LeaveGroup(sMan, _clientSocket, name, pass);
        break;
    
    case TLV_CREATE_GROUP:
        CreateNewGroup(sMan, _clientSocket, name, pass);
        break;
    
    case TLV_GROUP_LIST:
        GetGroupList(sMan, _clientSocket, name);
        break;

    case TLV_LOG_OUT:
        LogOut(sMan, _clientSocket, name);
        break;
    
    default:
        break;
    }
    return 1;
}

static int NewClient(int _clientSocket)
{
    return 1;
}
static int CloseClient(int _clientSocket)
{
    return 1;
}
static void Fail(Server* _server, int _clientSocket, void* _buffer, void* context)
{
    if(!_server)
    {
        puts("NULL server pionter at Fail");
        return;
    }
}

void Registration(ServerManager* _sMan, int _clientSocket, char* _usrName, char* _pass)
{
    ADTResult addResullt;
    char msg[MAX_NAME_LENGTH], buffer[BUFFER_SIZE];
    size_t packSize;
    
    ADTResultHandler(addResullt = AddUser(_sMan->m_users, _usrName, _pass), __func__);
    
    packSize = Pack(buffer, (char*)&addResullt, NULL, TLV_RPLY);
    SendMessage(_sMan->m_server, _clientSocket, buffer, packSize);
}

void LogIn(ServerManager* _sMan, int _clientSocket, char* _usrName, char* _pass)
{
    ADTResult loginResullt;
    char msg[MAX_NAME_LENGTH], buffer[BUFFER_SIZE];
    size_t packSize;

    ADTResultHandler(loginResullt = ManagerLoginUser(_sMan->m_users, _usrName, _pass), __func__);
    
    packSize = Pack(buffer, (char*)&loginResullt, NULL, TLV_RPLY);
    SendMessage(_sMan->m_server, _clientSocket, buffer, packSize);
}

void JoinGroup(ServerManager* _sMan, int _clientSocket, char* _gName, char* _usrName)
{
    ADTResult addGroupResult;
    size_t packSize;
    char *ip, port[sizeof(int) + 1], buffer[BUFFER_SIZE];

    ADTResultHandler(addGroupResult = AddUserToGroup( _sMan->m_users, _usrName, _gName), __func__);
    if(addGroupResult == SUCCESS)
    {
        /*should be in GroupManager*/
        sprintf(port, "%d", CHAT_PORT);
        ip = ManageGroupAddUser(_sMan->m_groups, _gName, _usrName);
        packSize = Pack(buffer, ip, port, TLV_GROUP_ADD);
    }
    else
    {
        packSize = Pack(buffer, (char*)&addGroupResult, NULL, TLV_RPLY);
    }

    SendMessage(_sMan->m_server, _clientSocket, buffer, packSize);
}

void LeaveGroup(ServerManager* _sMan, int _clientSocket, char* _gName, char* _usrName)
{
    ADTResult removeGroupResult, removeUserResult;
    size_t packSize;
    char buffer[BUFFER_SIZE];
    
    ADTResultHandler(removeGroupResult = RemoveGroupFromUser( _sMan->m_users, _usrName, _gName), "RemoveGroupFromUser");
    if(removeGroupResult == SUCCESS)
    {
    	ADTResultHandler(removeUserResult = ManageGroupRemoveUser( _sMan->m_groups, _gName, _usrName), "ManageGroupRemoveUser");
    }
    /*return IP to que if group is deleted*/
    packSize = Pack(buffer, (char*)&removeUserResult, NULL, TLV_GROUP_REMOVE);
    SendMessage(_sMan->m_server, _clientSocket, buffer, packSize);
}

void CreateNewGroup(ServerManager* _sMan, int _clientSocket, char* _gName, char* _usrName)
{
    ADTResult newGroupResult;
    QueueResult queRes;
    size_t packSize;
    char *ip, buffer[BUFFER_SIZE], port[sizeof(int) + 1];
    
    if((QueueRemove(_sMan->m_ipPool, &ip)) == QUEUE_SUCCESS)
    {
        ADTResultHandler(newGroupResult = AddNewGroup(_sMan->m_groups, _gName, ip), __func__);
        if( newGroupResult == SUCCESS )
        {
        	sprintf(port, "%d", CHAT_PORT);
            printf("\nport str: %s at %s\n", port, __func__);
        	ADTResultHandler(AddUserToGroup( _sMan->m_users, _usrName, _gName), __func__);
            ManageGroupAddUser(_sMan->m_groups, _gName, _usrName);
        	packSize = Pack(buffer, ip, port, TLV_GROUP_ADD);
        }
        else
        {
        	packSize = Pack(buffer, (char*)&newGroupResult, NULL, TLV_RPLY);
        }
    }
    else
    {
        newGroupResult = SERVER_IS_FULL;
        packSize = Pack(buffer, (char*)&newGroupResult, NULL, TLV_RPLY);
    }
    
    SendMessage(_sMan->m_server, _clientSocket, buffer, packSize);
}

static void GetGroupList(ServerManager* _sMan, int _clientSocket, char* _usrName)
{
    char buffer[BUFFER_SIZE], nameString[MAX_GROUPS * MAX_NAME_LENGTH], numOfGroups[sizeof(size_t) + 1];
    size_t packSize;
    strcpy(nameString, GetStringNames(_sMan->m_groups));
    
    if(nameString && (0 < GetNumOfGroups(_sMan->m_groups)))
    {
        printf("nameString: %s at %s", nameString, __func__);
        sprintf(numOfGroups, "%ld", GetNumOfGroups(_sMan->m_groups));
        packSize = Pack(buffer, nameString, numOfGroups, TLV_GROUP_LIST);
    }
    else
    {
        packSize = Pack(buffer, nameString, NULL, TLV_RPLY);
    }

    SendMessage(_sMan->m_server, _clientSocket, buffer, packSize);
}

static void LogOut(ServerManager* _sMan, int _clientSocket, char* _usrName)
{
    LogOutUser(_sMan->m_users, _usrName);
}

Queue* CreateIpPool(void)
{
	Queue* ipPool = NULL;
	QueueResult result;
	char* ip, i;
	if( ( ipPool = QueueCreate( MAX_GROUPS ) ) == NULL )
	{
		return NULL;
	}
	for( i = 0; i < MAX_GROUPS; ++i )
	{
		if( ( ip = (char*)malloc( IP_LEN * sizeof( char ) ) ) == NULL )
		{
			return NULL;
		}
		sprintf(ip, "224.0.0.%d", i );
		result = QueueInsert(ipPool, ip);
	}
	return ipPool;
}