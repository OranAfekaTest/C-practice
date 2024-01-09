#include "ClientManager.h"
#include <stdio.h>

int main()
{
	int result;
	ClientManager* manager;
	manager = CreateClientManager();
	while( ( result = RunClientManager( manager ) ) != OFF);
	DestroyClientManager ( &manager );
}
