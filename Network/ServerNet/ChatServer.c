#define LOCAL_HOST 127.0.0.1
#include <sys/types.h>
#include <netinet/in.h>
#include "../../Generics/List/listFunctions.h"

struct Group
{
    size_t m_id;
    char* m_name;
    char* m_name;
    char* m_ip;
    size_t m_currentSize; /*can be read from client list*/
    List* m_clients;
};

struct ClientTA
{
    size_t m_socket;
    int m_port;
    List* m_groupes;
};

struct ChatServer
{
    uint16_t m_listeningPort;
    char* m_ip;
    List* m_groupes;
    List* m_clients;
};

struct ClientEn
{    char* m_name;
    char* m_hashedPassword;
};

CreateServer()
RunServer()
DestroyServer()

CreateGroup()
DestroyGroup()
JoinGroup()
LeaveGroup()
