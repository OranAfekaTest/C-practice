#include <stdio.h>
int main ()
{
  unsigned int x = 0x76543210;
  Max(2 ,5);

  return 0;
}

void isLE(unsigned int x)
{
    char *c = (char*) &x;
 
    printf ("*c is: 0x%x\n", *c);
    if (*c == 0x10)
    {
      printf ("Underlying architecture is little endian. \n");
    }
    else
    {
       printf ("Underlying architecture is big endian. \n");
    }
 
}

int Max(int _a, int _b)
{
    int c = _a - _b;
    int sign = c >> (sizeof(int)*8 - 1) & 1;
    printf("sign is %d\n", sign);
    return _a - c * sign;
}