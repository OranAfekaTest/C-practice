#ifndef __GROUP_MANAGER_H__
#define __GROUP_MANAGER_H__
#include "ADTUtils.h"

typedef struct GroupManager GroupManager;

GroupManager* CreateGroupManager(size_t _capacity, int _port);
void DestroyGroupManager(GroupManager** _gMan);
ADTResult AddNewGroup(GroupManager* _gMan, char* _name, char* _ip);
char* ManageGroupAddUser(GroupManager* _gMan, char* _grpName, char* _user);/*returns group IP in succes*/
char* GetStringNames(GroupManager* _gMan);
size_t GetNumOfGroups(GroupManager* _gMan);
ADTResult ManageGroupRemoveUser(GroupManager* _gMan, char* _grpName, char* _user);/* returns TRUE if group is empty and FALSE otherwise*/

#endif /* __GROUP_MANAGER_H__ */