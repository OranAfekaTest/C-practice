#include <dlfcn.h>
#include <stdio.h>

typedef void (*dlFunc)(void);

int main(void)
{
    dlFunc dlPrint;
    void* dl = dlopen("testLib.so", RTLD_LAZY);
    if(!dl)
    {
        puts("dlopen failed.");
        return 1;
    }
    dlPrint = (dlFunc)dlsym(dl, "libPrint");
    if(!dlPrint)
    {
        puts("dlsym failed.");
        return 1;
    }
    puts("before dlPrint");
    dlPrint;
    puts("after dlPrint");
    dlclose(dl);
    return 0;
}