#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__
#include "ADTUtils.h"

typedef enum MenuSwitch{
						REGISTRATION = 1,
						LOG_IN,
						EXIT,
						JOIN_GROUP,
						LEAVE_GROUP,
						CREATE_GROUP,
						LOG_OUT
						} MenuSwitch;


typedef struct ClientManager ClientManager;

ClientManager* CreateClientManager();

int RunClientManager(ClientManager* _Client );

void DestroyClientManager(ClientManager** _manager);

#endif

