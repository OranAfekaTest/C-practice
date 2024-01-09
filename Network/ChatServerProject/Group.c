#include "Group.h"
#include "../../Generics/Hash/hashMap.h"
#include <stdlib.h>
#define MAGICNUM 68745217

struct Group
{
    char m_name[MAX_NAME_LENGTH];
    char m_ip[MAX_NAME_LENGTH];
    HashMap* m_users;
    int m_magicNum;
};

Group* CreateGroup(char* _name, char* _ip)
{
    Group* group = NULL;
    if(!_name || !_ip)
    {
        return group;
    }
    
    group = malloc(sizeof(Group));
    if(!group)
    {
        return NULL;
    }
    
    group->m_users = HashMapCreate(BACK_LOG, HashFunc, KeyComperator);
    if(!group->m_users)
    {
        free(group);
        return NULL;
    }

    strcpy(group->m_name, _name);
    strcpy(group->m_ip, _ip);

    return group;
}

void DestroyGroup(Group* _group)
{
    if(_group)
    {
        if(_group->m_magicNum == MAGICNUM)
        {
            HashMapDestroy(&_group->m_users, NULL, NULL);
            _group->m_magicNum = 0;
            free(_group);
        }
    }
}

const char* GroupGetName(Group* _grp)
{
    if(!_grp)
    {
        return NULL;
    }
    return _grp->m_name;
}

size_t GetGroupSize(Group* _grp)
{
    if(!_grp)
    {
        return 0;
    }
    return VectorSize(_grp->m_users);
}

const char* GroupAddUser(Group* _grp, char* _user)
{
    if(!_grp || !_user)
    {
        return NULL;
    }
    
    if(MAP_SUCCESS != (HashMapInsert(_grp->m_users, _user, NULL) ) )
    {
        return NULL;
    }

    return _grp->m_ip;
}

ADTResult GroupRemoveUser(Group* _grp, char* _user) /* returns true if group is empty */
{
	void** userRemoved;
    if(!_grp || !_user)
    {
        return FAIL;
    }
    
    if( (HashMapRemove(_grp->m_users, _user, userRemoved, NULL) ) != MAP_SUCCESS)
    {
        return FAIL;
    }
	
	if( HashMapSize( _grp->m_users) == 0 )
	{
		return EMPTY_GROUPS;
	}
	return SUCCESS;
}
