#include <stdio.h>
#include <string.h>
#define BITS_IN_BYTES 8

int InvertBits(unsigned char x, unsigned char* y);
void PrintBits(unsigned char x);
int RotateBits(unsigned char x, int rotation);
void CompresString(char* C);
int ReverseBits(unsigned char x);
int IsBitPalindrom(unsigned char x);
void SetBits(unsigned char* _x, int _p, unsigned char _n, unsigned char _y);
void SetBits2(unsigned int* w,int i,int j,int value);

int main(void)
{
	unsigned char val = 237, bits;
	char str[] = "abcdefghijklmno";
	char* ptr = str;
	printf("InvertBits\n");
	PrintBits(val);
	InvertBits(val, &bits);
	PrintBits(bits);
	printf("\n*****************\nRotateBits\n");
	PrintBits(val);
	bits = RotateBits(val, 3);
	PrintBits(bits);
	printf("\n*****************\nCompresString\n");
	CompresString(str);
	while(*ptr != '\0')
	{
		PrintBits(*ptr);
		ptr++;
	}
	printf("\n*****************\nReverseBits\n");
	PrintBits(val);
	bits = ReverseBits(val);
	PrintBits(bits);
	printf("\n*****************\nIsBitPalindrom\n");
	PrintBits(189);
	printf("%s.\n", (IsBitPalindrom(189) ? "yes" : "no"));
	printf("\n*****************\nSetBits\n");
	printf("set the 7 position of ");
	PrintBits(bits);
	printf("to the 2 first bits of ");
	PrintBits(val);
	SetBits(&bits, 7, 2, val);
	PrintBits(bits);
	printf("\n*****************\nSetBits2\n");
}

int InvertBits(unsigned char _x, unsigned char* _y)
{
	unsigned char mask = 0xff;
	if(!_y)
	{
		return 1;
	}
	*_y = _x ^ mask;
	return 0;
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

int RotateBits(unsigned char _x, int _rotation)
{
	unsigned char mask = 0;
	int i, offset;
	_rotation %= BITS_IN_BYTES;
	for(i = 0; i < _rotation; i++)
	{
		mask |= 1 << i;
	}
	offset = BITS_IN_BYTES - _rotation;
	mask &= _x;
	_x >>= _rotation;
	return _x |= (mask << offset);
}

int checkString(char* _str)
{
	int i, len = strlen(_str);
	if(!_str)
	{
		return 1;
	}
	for(i = 0; i < len; i++)
	{
		if(_str[i] < 97 || 111 < _str[i])
		{
			return 1;
		}
	}
	return 0;
}

void CompresString(char* _C)
{
	int i, len = strlen(_C);
	unsigned char compressedByte = 0;
	if(checkString(_C))
	{
		return;
	}
	for(i = 0; i < len; i++)
	{
		if(i % 2 == 0)
		{
			compressedByte = _C[i] - 96;
		}
		else
		{
			compressedByte += (_C[i] - 96) << (BITS_IN_BYTES/2);
			_C[i / 2] = compressedByte;
		}
	}
	if(len % 2 == 0)
	{
		_C[i / 2] = '\0';
	}
	else
	{
		_C[i / 2] = compressedByte;
		_C[i / 2 + 1] = '\0';
	}
}

int ReverseBits(unsigned char _x)
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

int IsBitPalindrom(unsigned char _x)
{
	unsigned char reversed = ReverseBits(_x);
	return (_x == reversed);
}

void SetBits(unsigned char* _x, int _p, unsigned char _n, unsigned char _y)
{
	int i;

	for(i = 0; i < _n; i++)
	{
		if(_y & (1 << i))
		{
			*_x |= 1 << (_p - _n) + i;
		}
		else
		{
			*_x &= ~(1 << (_p - _n) + i);
		}
	}
}

void SetBits2(unsigned int* _w,int _i,int _j,int _value)
{
	int itr;
	
	if(_value != 0 || _value != 1 || _i < 0 || _j < 0 || 31 < _i || 31 < _j)
	{
		return;
	}
	if(_value)
	{
		for(itr = _i; itr <= _j; itr++)
		{
			*_w |= _value << itr;
		}
	}
	else
	{
		for(itr = _i; itr <= _j; itr++)
		{
			*_w &= ~(~_value << itr);
		}
	}
}
