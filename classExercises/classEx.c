#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int d[] = {1, 5, 7};
int *p = &d[1];
printf("%d", *p--);
printf("%d", *p);
printf("%d%d%d", d[0],d[1],d[2]);
	return 0;
}
