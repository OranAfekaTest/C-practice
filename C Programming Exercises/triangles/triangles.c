#include "triangles.h"


int CheckParameters(int _size , char _charToPaint )
{
    if(_size < MIN_SIZE || _size > MAX_SIZE)
    {
        return SIZE_ERROR;
    }
    if(_charToPaint < FIRST_SHAPE || _charToPaint > LAST_SHAPE)
    {
        return SHAPE_ERROR;
    }
    return OK;
}

void PrintLine(int _size, char _charToPaint, int _flag)
{
    int i;
    for ( i = 0 ;  i < _size  ; i++)
    {
        if(_flag == 1) putchar(' ');
        putchar(_charToPaint);
        if(_flag == 2) putchar(' ');
    }
}

int StraightAngle(int _size, char _charToPaint)
{
    int i, j, result;

    if((result = CheckParameters(_size , _charToPaint)) != OK)
    {
        return result;
    }

    for(i = 0; i < _size; i++ )
    {
        PrintLine(i + 1, _charToPaint, 0);
        putchar('\n');
    }

    return OK;
}

int ReversedStraightAngle(int _size, char _charToPaint)
{
    int i, j;

    for(i = 0; i < _size; i++ )
    {
        PrintLine(_size - i, _charToPaint, 0);
        putchar('\n');
    }

    return OK;
}

int Triangleisosceles(int _size, char _charToPaint)
{
    Func1(_size, _charToPaint);
    Func2(_size-1, _charToPaint);
}

int Pyramid(int _size, char _charToPaint)
{
    int i, j, k;

    for(i = 0; i < _size; i++ )
    {
        PrintLine(_size - i, ' ', 0);
        PrintLine(i + 1, _charToPaint, 2);
        putchar('\n');
    }
}

int ReversedPyramid(int _size, char _charToPaint)
{
    int i, j, k;

    for(i = 0; i < _size; i++ )
    {
        PrintLine(i + 1, ' ', 0);
        PrintLine(_size - i, _charToPaint, 1);
        printf("\n");
    }
}

int Diamond(int _size, char _charToPaint)
{
    Func4(_size, _charToPaint);
    Func5(_size-1, _charToPaint);
}