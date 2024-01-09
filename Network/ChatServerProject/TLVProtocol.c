#include "TLVProtocol.h"
#include <string.h>
#include <stdio.h>


/*
static void UnpackRegistration( char* _package, char* _name, char* _password );
static void PackRegistration( char* _package, char* _name, char* _password );
static void PackReply(char* _package, char* _rsltCode);
static void UnpackReply(char* _package, char* _rsltCode);

void Pack( char* _package, char* _str1, char* _str2, Tags _tag )
{
	if( !_str1 || !_tag )
	{
		return;
	}
	switch( _tag )
	{
		case TLV_REG_REQ:
			PackRegistration( _package, _str1, _str2 );
			break;
		
		case TLV_RPLY:
			PackReply(_package, _str1);
			break;
	}
}

unsigned char Unpack( char* _package, char* _str1, char* _str2 )
{
	if( !_str1 || !_package )
	{
		return;
	}
	switch( _package[0] )
	{
		case TLV_REG_REQ:
			UnpackRegistration( _package, _str1, _str2 ); 
			break;
		
		case TLV_RPLY:
			UnpackReply(_package, _str1);
			break;
	}
	return _package[0];
}

static void PackRegistration( char* _package, char* _name, char* _password )
{
	char totalLength, nameLength, passLength;
	nameLength = strlen( _name ) + 1;
	passLength = strlen( _password ) + 1;
	totalLength = nameLength + passLength;
	_package[0] = TLV_REG_REQ;
	_package[1] = totalLength + 2;
	_package[2] = nameLength;
	strcpy( _package + 3, _name );
	_package[ 3 + nameLength ] =  passLength;
	strcpy( _package + nameLength + 4, _password );
}

static void UnpackRegistration( char* _package, char* _name, char* _password )
{
	strcpy( _name, _package + 3 );
	strcpy( _password, _package + 4 + _package[2] );
}


static void PackReply(char* _package, char* _rsltCode)
{
	char totalLength;
	totalLength = strlen( _rsltCode ) + 1;
	_package[0] = TLV_RPLY;
	_package[1] = totalLength;
	strcpy( _package + 2, _rsltCode );
}

static void UnpackReply(char* _package, char* _rsltCode)
{
	strcpy( _rsltCode, _package + 2 );

}
*/
size_t Pack( char* _package, char* _str1, char* _str2, Tags _tag )
{
	char totalLength, nameLength, passLength;
	if( _str1 && _tag )
	{
		if( _str2 )
		{
			nameLength = strlen( _str1 ) + 1;
			passLength = strlen( _str2 ) + 1;
			totalLength = nameLength + passLength + 2;
			_package[0] = _tag;
			_package[1] = totalLength + 2;
			_package[2] = nameLength;
			strcpy( _package + 3, _str1 );
			_package[ 3 + nameLength ] =  passLength;
			strcpy( _package + nameLength + 4, _str2 );
		}
		else
		{
			totalLength = strlen( _str1 ) + 1;
			_package[0] = _tag;
			_package[1] = totalLength;
			strcpy( _package + 2, _str1 );
		}
	}
	return ((int)totalLength) + 2;
}

unsigned char Unpack( char* _package, char* _str1, char* _str2 )
{
	if( _str1 )
	{
		if( _str2 )
		{
			strcpy( _str1, _package + 3 );
			strcpy( _str2, _package + 4 + _package[2] );
		}
		else
		{
			strcpy( _str1, _package + 2 );
		}
	}
	return _package[0];
}