#include "GroupManager.h"
#include "Group.h"
#include "../../Generics/Hash/hashMap.h"
#include <stdlib.h>

typedef struct GroupNames{
    char m_nameString[MAX_GROUPS * MAX_NAME_LENGTH];
} GroupNames;

struct GroupManager
{
    HashMap* m_groups;
    GroupNames m_groupNames;
    int m_chatPort;
};

static int StringNames(const void* _key, void* _value, void* _context);

GroupManager* CreateGroupManager(size_t _capacity, int _port)
{
    GroupManager* gMan = malloc(sizeof(GroupManager));
    
    if(!gMan || _port < 0)
    {
        return NULL;
    }
    if((gMan->m_groups = HashMapCreate(_capacity, HashFunc, KeyComperator)) == NULL)
    {
        free(gMan);
        return NULL;
    }

    gMan->m_chatPort = _port;

    return gMan;
}

void DestroyGroupManager(GroupManager** _gMan)
{
    if(*_gMan)
    {
        free(*_gMan);
        *_gMan = NULL;
    }
}

ADTResult AddNewGroup(GroupManager* _gMan, char* _name, char* _ip)
{
    Group* nGrp = NULL;
    if(!_gMan || !_name)
    {
        return UNINITIALIZED;
    }
    if((nGrp = CreateGroup(_name, _ip)) == NULL)
    {
        return ALLOCATION_ERROR;
    }
    if((HashMapInsert(_gMan->m_groups, GroupGetName(nGrp), nGrp)) == MAP_KEY_DUPLICATE_ERROR)
    {
        return INVALID_NAME;
    }
    
    return SUCCESS;
}

char* ManageGroupAddUser(GroupManager* _gMan, char* _grpName, char* _user)
{
    Group* nGrp = NULL;
    if(!_gMan || !_grpName || !_user)
    {
        return NULL;
    }
    if((HashMapFind(_gMan->m_groups, _grpName, &nGrp)) != MAP_SUCCESS)
    {
        return NULL;
    }
    
    return GroupAddUser(nGrp, _user);
}

size_t GetNumOfGroups(GroupManager* _gMan)
{
    if(!_gMan)
    {
        return 0;
    }
    return HashMapSize(_gMan->m_groups);
}

char* GetStringNames(GroupManager* _gMan)
{
    if(!_gMan)
    {
        return NULL;
    }
    
    HashMapForEach(_gMan->m_groups, StringNames, &_gMan->m_groupNames);
    printf("nameString: %s at %s\n", _gMan->m_groupNames.m_nameString, __func__);
    return _gMan->m_groupNames.m_nameString;
}

int	StringNames(const void* _key, void* _value, void* _context)
{
    char* names = ((GroupNames*)_context)->m_nameString;
    strcat(names, (const char*)_key);
    strcat(names, "\n");
    return 1;
}

ADTResult ManageGroupRemoveUser(GroupManager* _gMan, char* _grpName, char* _user)
{
    Group* nGrp = NULL;
    ADTResult result;
    void** removedGroup;
    if(!_gMan || !_grpName || !_user)
    {
        return UNINITIALIZED;
    }
    if((HashMapFind(_gMan->m_groups, _grpName, (void**)&nGrp)) != MAP_SUCCESS)
    {
        return INVALID_NAME;
    }
    if( ( result = GroupRemoveUser(nGrp, _user) ) == EMPTY_GROUPS )
    {
    	HashMapRemove( _gMan->m_groups, _grpName, removedGroup, NULL );
    }
    return SUCCESS;
}
