#include "homeWork1.h"

int main(void)
{
    char cahrToPaint;
    int size;

    printf("Please enter triangle base size and a har to paint:\n");
    scanf("%d %c", &size, &cahrToPaint);

    printf("Calling Func1:\n");
    Func1(size, cahrToPaint);
    printf("Calling Func2:\n");
    Func2(size, cahrToPaint);
    printf("Calling Func3:\n");
    Func3(size, cahrToPaint);
    printf("Calling Func4:\n");
    Func4(size, cahrToPaint);
    printf("Calling Func5:\n");
    Func5(size, cahrToPaint);
    printf("Calling Func6:\n");
    Func6(size, cahrToPaint);
}

void Func1(int _size, const char _cahrToPaint)
{
    int i, j;

    for(i = 0; i < _size; i++ )
    {
        for(j = 0; j <= i; j++)
        {
            printf("%c", _cahrToPaint);
        }
        printf("\n");
    }
}

void Func2(int _size, const char _cahrToPaint)
{
    int i, j;

    for(i = 0; i < _size; i++ )
    {
        for(j = i; j < _size; j++)
        {
            printf("%c", _cahrToPaint);
        }
        printf("\n");
    }
}

void Func3(int _size, const char _cahrToPaint)
{
    Func1(_size, _cahrToPaint);
    Func2(_size-1, _cahrToPaint);
}

void Func4(int _size, const char _cahrToPaint)
{
    int i, j, k;

    for(i = 0; i < _size; i++ )
    {
        for(j = i; j < _size; j++)
        {
            printf(" ");
        }
        
        for(k = 0; k <= i; k++)
        {
            printf("%c ", _cahrToPaint);
        }
    printf("\n");
    }
}

void Func5(int _size, const char _cahrToPaint)
{
    int i, j, k;

    for(i = 0; i < _size; i++ )
    {
        for(j = 0; j <= i; j++)
        {
            printf(" ");
        }
        for(k = i; k < _size; k++)
        {
            printf(" %c", _cahrToPaint);
        }
        printf("\n");
    }
}

void Func6(int _size, const char _cahrToPaint)
{
    Func4(_size, _cahrToPaint);
    Func5(_size-1, _cahrToPaint);
}