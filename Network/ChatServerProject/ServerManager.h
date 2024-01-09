#ifndef _SERVER_MANGER_H_
#define _SERVER_MANGER_H_
/*documentation*/
typedef struct ServerManager ServerManager;

ServerManager* CreateServerManager(void);

void RunServer(ServerManager* _sMan);

void DestroyServerManager(ServerManager** _sMan);

#endif /*_SERVER_MANGER_H_*/
