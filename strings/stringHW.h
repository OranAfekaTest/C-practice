#define OK 0
#define NULL_POINTER_EXCEPTION 1
#define LOCATION_ERROR -1
#define TRUE 1
#define FALSE 0

/* description - drlrts each character sin string s1 that matches any character in the string s2.
input- two strings s1 and s2.
output- OK or Errors
errors- 1: Null pointer */
int Squeeze(char* s1, char* s2);

/* description - returns the lacation of string s2 int the
string s1. is s1 doesn't contain s2 then return -1.
input- two strings s1 and s2.
output- the index of where substring s2 begins within s1.
errors- -1: Null pointer */
int Location(char* s1, char* s2);

/* description - trim multiple consecutive spaces to one
space in a string.
input- a string.
output- OK or Errors
errors- 1: Null pointer */
int STrim(char* str);
