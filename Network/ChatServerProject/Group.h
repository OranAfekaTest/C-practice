#ifndef _GROUP_H_
#define _GROUP_H_
#include "ADTUtils.h"

typedef struct Group Group;

Group* CreateGroup(char* _name, char* _ip);
void DestroyGroup(Group* _group);
size_t GetGroupSize(Group* _grp);
const char* GroupAddUser(Group* _grp, char* _usrName);/*Get IP on Success*/
const char* GroupGetName(Group* _grp);
ADTResult GroupRemoveUser(Group* _grp, char* _user);


#endif /*_GROUP_H_*/