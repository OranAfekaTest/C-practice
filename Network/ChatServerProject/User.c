#include "../../Generics/Hash/hashMap.h"
#include "User.h"
#include <stdlib.h> /* malloc */
#define MAGICNUM 6842532

struct User{ 
            char m_name[MAX_NAME_LENGTH];
            char m_password[MAX_NAME_LENGTH];
            int m_isActive;
            HashMap* m_groups;
            int m_magicNum;
            };

User* CreateUser( char* _name, char* _password )
{
    User* user;
    if( !_name || !_password )
    {
        return NULL;
    }
    if( ( user = ( User* )malloc(sizeof( User ) ) ) == NULL )
    {
        return NULL;
    }
    if((user->m_groups = HashMapCreate(MAX_GROUPS, HashFunc, KeyComperator)) == NULL)
    {
        free (user);
        return NULL;
    }
    strcpy(user->m_name, _name);
    strcpy(user->m_password, _password);
    user->m_isActive = 0;
    user->m_magicNum = MAGICNUM;
    return user;
} 

void DestroyUser( User* _user )
{
    if(_user)
    {
        if(_user->m_magicNum == MAGICNUM)
        {
            HashMapDestroy(&_user->m_groups, NULL, NULL);
            _user->m_magicNum = 0;
            free(_user);
        }
    }
}

ADTResult LoginUser( User* _user, char* _password )
{
	if( !_user )
	{
		return UNINITIALIZED;
	}

	if( strcmp( _user->m_password, _password ) )
	{
		return INVALID_PASSWORD;
	}
	_user->m_isActive = TRUE;
	return SUCCESS;
}
	

const char* GetUserName( User* _user )
{
    if( !_user )
    {
        return NULL;
    }
    return _user->m_name;
}

ADTResult UserJoinGroup(User* _usr, char* _grpName)
{
    if(!_usr || !_grpName)
    {
        return UNINITIALIZED;
    }

    if((HashMapInsert(_usr->m_groups, _grpName, NULL)) != MAP_SUCCESS)
    {
        puts("INVALID_NAME at AddUserToGroup");
        return INVALID_NAME;
    }
    
    return SUCCESS;
}

ADTResult UserRemoveGroup(User* _usr, char* _grpName)
{
	void** grpRemoved;
    if(!_usr || !_grpName)
    {
        return UNINITIALIZED;
    }

    if((HashMapRemove(_usr->m_groups, _grpName, grpRemoved, grpRemoved)) != MAP_SUCCESS)
    {
        puts("INVALID_NAME at UserRemoveGroup");
        return INVALID_NAME;
    }
    
    return SUCCESS;
}

ADTResult UserLogOut(User* _usr)
{
    if(!_usr)
    {
        return UNINITIALIZED;
    }
    _usr->m_isActive = FALSE;
    return SUCCESS;
}