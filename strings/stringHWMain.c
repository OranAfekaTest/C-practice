#include <stdio.h>
#include "stringHW.h"


int main(void)
{
	char s1[] = "ASDFGH", s2[] = "DAG", loc[] = "SD", strim[] = "Ganan      gidel     dagan     bagan";
	int status = 0;
	
	/*printf("Squeeze(%s, %s): ", s1, s2);
	status += Squeeze(s1, s2);
	printf("%s \n", s1);
	*/
	printf("Location of %s within %s is %d \n", s2, s1, Location(s1, s2));
	printf("Location of %s within %s is %d \n", loc, s1, Location(s1, loc));
	
	status += STrim(strim);
	printf("%s \n", strim);
	
	return status;
}
