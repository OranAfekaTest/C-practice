#include "../../Generics/Hash/hashMap.h"
#include "UserManager.h"
#include <stdlib.h> /* malloc */
#include <math.h> /* pow */
#include <string.h> /* strlen */
#include <stdio.h> /* result handler */

struct UserManager{ 
                HashMap* m_users;
                int m_numOfUsers;
            };

UserManager* CreateUserManager( size_t _capacity )
{
    UserManager* userManager = NULL;
    HashMap* users = NULL;
    if( ( userManager = ( UserManager* )malloc( sizeof( UserManager ) ) ) == NULL )
    {
        return NULL;
    }
    if( ( users = HashMapCreate( _capacity, HashFunc, KeyComperator ) ) == NULL )
    {
        free( userManager );
        return NULL;
    }
    userManager->m_users = users;
    userManager->m_numOfUsers = 0;
    return userManager;
}

void DestroyUserManager(UserManager** _userMan)
{
    if(*_userMan)
    {
        HashMapDestroy(&(*_userMan)->m_users, free, DestroyUser);
        free(*_userMan);
        *_userMan = NULL;
    }
}

ADTResult AddUser( UserManager* _userMan, char* _name, char* _password  )
{
    User* newUser = NULL;
    if( !_userMan || !_name || !_password )
    {
        return UNINITIALIZED;
    }
    if( ( newUser = CreateUser( _name, _password ) ) == NULL )
    {
        return ALLOCATION_ERROR;
    }
    if( ( HashMapInsert( _userMan->m_users, GetUserName(newUser), newUser ) ) != MAP_SUCCESS )
    {
        DestroyUser( newUser );
        return INVALID_NAME;
    }
    ++_userMan->m_numOfUsers;
    return SUCCESS;
}

ADTResult ManagerLoginUser( UserManager* _userMan, char* _name, char* _password  )
{
    User* user = NULL;
    if( !_userMan || !_name || !_password )
    {
        return UNINITIALIZED;
    }
    if( ( HashMapFind( _userMan->m_users, _name, &user ) ) != MAP_SUCCESS )
    {
        return INVALID_NAME;
    }
    
	if( LoginUser( user, _password ) != SUCCESS )
	{
		return INVALID_PASSWORD;
	}
    return SUCCESS;
}

ADTResult AddUserToGroup( UserManager* _userMan, char* _usrName, char* _gName )
{
	User* user = NULL;
	if( ( HashMapFind( _userMan->m_users, _usrName, &user ) ) != MAP_SUCCESS )
    {
        return INVALID_NAME;
    }
    
    return UserJoinGroup( user, _gName );
}

ADTResult RemoveGroupFromUser( UserManager* _userMan, char* _usrName, char* _gName )
{
	User* user = NULL;
	if( ( HashMapFind( _userMan->m_users, _usrName, &user ) ) != MAP_SUCCESS )
    {
        return INVALID_NAME;
    }
    return UserRemoveGroup( user, _gName );
 }

ADTResult LogOutUser(UserManager* _userMan , char* _usrName)
{
    User* user = NULL;
    if(!_userMan || !_usrName)
    {
        return UNINITIALIZED;
    }
    if( ( HashMapFind( _userMan->m_users, _usrName, &user ) ) != MAP_SUCCESS )
    {
        return INVALID_NAME;
    }
    return UserLogOut(user);
}