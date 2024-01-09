#ifndef __USER_H__
#define __USER_H__
#include "ADTUtils.h"

typedef struct User User;

User* CreateUser( char* _name, char* _password );

void DestroyUser( User* _user );

const char* GetUserName( User* _user );

ADTResult LoginUser( User* _user, char* _password );

ADTResult UserJoinGroup(User* _usr, char* _grpName);

ADTResult UserRemoveGroup(User* _usr, char* _grpName);

ADTResult UserLogOut(User* _usr);

#endif /* __USER_H__ */