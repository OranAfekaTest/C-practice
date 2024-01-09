#include <stdio.h>
#define BITS_IN_BYTES 8
#define LUTSize 256

static void BuildLookUpTable(unsigned char *_table, int _size, unsigned char (*_bitFunction)(unsigned char _input));
static unsigned char BitCount(unsigned char _input);
static unsigned char LUTBitCount(unsigned char _input);
static unsigned char ReverseBits(unsigned char _input);
static unsigned char LUTReverseBits(unsigned char _input);
static unsigned char SwapOddEven(unsigned char _input);
static unsigned char LUTSwapOddEven(unsigned char _input);
static int IntBitCount(unsigned int _input);
static void PrintBits(unsigned char _x);


int main(void)
{
    unsigned char x = 0xCD, y = 0x7A;
    
    printf("bits in 821,674 = %d = 9\n",IntBitCount(821674));

    return 0;
}

void BuildLookUpTable(unsigned char *_table, int _size, unsigned char (*_bitFunction)(unsigned char _input))
{
    int i;
    for(i = 0; i < _size; i++)
    {
        _table[i] = _bitFunction((unsigned char)i);
    }
}

unsigned char BitCount(unsigned char _input)
{
    int i, counter = 0;
    
    for(i = 0; i < BITS_IN_BYTES; i++)
    {
        if((_input >> i) & 1)
        {
            counter++;
        }
    }
    return counter;
}

unsigned char LUTBitCount(unsigned char _input)
{
    static unsigned char cBits[LUTSize];
    static unsigned char flag;
    if(!flag)
    {
        BuildLookUpTable(cBits, LUTSize, BitCount);
    }
    return cBits[_input];
}

unsigned char ReverseBits(unsigned char _x)
{
	unsigned char reversed = 0;
	int i;
	
	for(i = 0; i < BITS_IN_BYTES; i++)
	{
		if(_x & (1 << i))
		{
			reversed |= 1 << (BITS_IN_BYTES - 1 - i);
		}
	}
	return reversed;
}

unsigned char LUTReverseBits(unsigned char _input)
{
    static unsigned char rBits[LUTSize];
    static unsigned char flag;
    if(!flag)
    {
        BuildLookUpTable(rBits, LUTSize, ReverseBits);
    }
    return rBits[_input];
}

unsigned char SwapOddEven(unsigned char _input)
{
    unsigned char i, swap, evenMask = 0xAA, oddMask = 0x55;
    swap = (_input & evenMask) >> 1;
    _input = (_input & oddMask) << 1;
    return _input | swap;
}

unsigned char LUTSwapOddEven(unsigned char _input) /* 10011001 -> 01100110 change indexes */
{
    static unsigned char sBits[LUTSize];
    static unsigned char flag;
    if(!flag)
    {
        BuildLookUpTable(sBits, LUTSize, SwapOddEven);
    }
    return sBits[_input];
}

void PrintBits(unsigned char _x)
{
	int i;
	for(i = BITS_IN_BYTES-1; 0 <= i; i--)
	{
		printf("%c", (_x & (1 << i) ? '1' : '0'));
	}
	putchar('\n');
}

int IntBitCount(unsigned int _input)
{
    int i, result = 0;
    unsigned char mask = 0xff;
    for(i = 0; i < sizeof(unsigned int); i++)
    {
        result += LUTBitCount(mask & (_input >> i*BITS_IN_BYTES));
    }
    
    return result;
}