#ifndef __USERMAN_H__
#define __USERMAN_H__
#include "User.h"

typedef struct UserManager UserManager;

UserManager* CreateUserManager( size_t _capacity );
ADTResult ManagerLoginUser( UserManager* _userMan, char* _name, char* _password  );
ADTResult AddUser( UserManager* _userMan, char* _userName , char* _password);
void DestroyUserManager(UserManager** _userMan); 
ADTResult AddUserToGroup( UserManager* _userMan, char* _usrName, char* _gName );
ADTResult RemoveGroupFromUser( UserManager* _userMan, char* _usrName, char* _gName );
ADTResult LogOutUser(UserManager* _userMan , char* _usrName);

#endif /* __USERMAN_H__ */