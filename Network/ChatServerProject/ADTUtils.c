#include "ADTUtils.h"
#include <string.h>
#include <stdio.h>
#include <math.h>


/*======= Static Declarations ========*/
static char* resultDescription[] = {
                            "Success",
                            "Uninitialized error",
                            "Allocation error",
                            "Invalid name",
                            "Invalid password",
                            "Failed to send message",
                            "Failed to receive message",
                            "Server is full",
                            
};
static size_t NearestPrime( size_t _n );


/*======= Utility Functions ========*/

void ADTResultHandler(ADTResult _code, const char* _location)
{
    if(_code)
	{
		printf("%s at %s\n", resultDescription[_code], _location);
	}
}

size_t HashFunc( const void* _key )
{
	size_t i = 0, res = 0;
	int size, m = 1e9 + 9;
	size = NearestPrime ( strlen( (char*)_key ) );
	while( ((char*)_key)[i] != '\0' )
	{
		res += ( (char*)_key )[i] * pow( size, i );
		++i;
	}
	return res % m;
}

static size_t NearestPrime( size_t _n )
{
    register size_t i;
    int isPrime = 0;
    while( isPrime == 0 )
    {
		if( _n == 0 )
		{
			return 0;
		}
        for( i = 2; i <= _n/2; ++i )
        {
            if( _n % i == 0 )
            {
                ++_n;
                break;
            }
        }
        isPrime = 1;
    }
    return _n;
}

int KeyComperator(void* _firstKey, void* _secondKey)
{
	return ( !strcmp( ( char* )_firstKey, ( char* )_secondKey) );
}
