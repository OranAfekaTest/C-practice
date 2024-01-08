#include <stdio.h>
#define MIN_SIZE 2
#define MAX_SIZE 60
#define FIRST_SHAPE '!'
#define LAST_SHAPE '~'
#define SIZE_ERROR 1
#define SHAPE_ERROR 2
#define OK 0


/* description - *
				 **
input- size of the base and a char to paint
output- status OK or Errors
errors- 1: size is out of bounds
		2: illegal character*/
int StraightAngle(int _size, char _charToPaint);

/* description -  *
				 **
input- size of the base and a char to paint
output- status OK or Errors
errors- 1: size is out of bounds
		2: illegal character*/
int ReversedStraightAngle(int _size, char _charToPaint);

/* description - *
				 **
				 *
input- size of the base and a char to paint
output- status OK or Errors
errors- 1: size is out of bounds
		2: illegal character*/
int Triangleisosceles(int _size, char _charToPaint);

/* description -  *
				 * *
input- size of the base and a char to paint
output- status OK or Errors
errors- 1: size is out of bounds
		2: illegal character*/
int Pyramid(int _size, char _charToPaint);

/* description - * *
				  *
input- size of the base and a char to paint
output- status OK or Errors
errors- 1: size is out of bounds
		2: illegal character*/
int ReversedPyramid(int _size, char _charToPaint);

/* description -  *
				 * *
				  *
input- size of the base and a char to paint
output- status OK or Errors
errors- 1: size is out of bounds
		2: illegal character*/
int Diamond(int _size, char _charToPaint);