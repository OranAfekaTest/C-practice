#include "ServerManager.h"
#include <stdlib.h>

int main(void)
{
    ServerManager* sMan = NULL;
    sMan = CreateServerManager();
    RunServer(sMan);
    DestroyServerManager(&sMan);

    return 0;
}