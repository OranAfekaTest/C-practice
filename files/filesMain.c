#define LINES 5
#define BUFFER_SIZE 256
#include <stdio.h>
#include <stddef.h>
#include <string.h>

int tail(char* fileName, char* buffer, int nLines);
int wordCount(char* _fileName, char* _buffer);
int letterFreq(char* _fileName);


int main(void)
{
	int cod, wc;
	
	char buffer[BUFFER_SIZE] = {0};
	
	
	cod = tail("moksha.txt", buffer, LINES);
	/*wc = wordCount("moksha.txt", buffer);*/
	/*letterFreq("small");*/
	
	printf("%s main\n", buffer);
	/*printf("%d\n", wc);*/
	return cod;
}

int tail(char* _fileName, char* _buffer, int _nLines)
{
	char tmpBuffer[BUFFER_SIZE];
	int i, counter = 0;
	size_t pos;
	FILE* fp = fopen(_fileName, "r");
	if(!fp)
	{
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	for(i = 1; i < pos; i += 2)
	{
		fseek(fp, pos - i, SEEK_SET);
		if(fgetc(fp) == '\n')
		{
			if(++counter >= _nLines)
			{
				while(counter--)
				{
					fgets(tmpBuffer, BUFFER_SIZE - 1, fp);
					_buffer = strcat(_buffer, tmpBuffer);
				}
				break;
			}
		}
	}
	fclose(fp);
	return 0;
}

int wordCount(char* _fileName, char* _buffer)
{
	int i, counter = 0;
	char* token = NULL;
	FILE* fp = fopen(_fileName, "r");
	if(!fp)
	{
		return 1;
	}
	fgets(_buffer, BUFFER_SIZE - 1, fp);
	while(!feof(fp))
	{
		token = strtok(_buffer, " \n\t");
		while(token)
		{
			counter++;
			/*printf("%s %d\n", token, counter);*/
			token = strtok(NULL, " \n\t");
		}
		fgets(_buffer, BUFFER_SIZE - 1, fp);
	}
	fclose(fp);
	return counter;
}

int letterFreq(char* _fileName)
{
	int c, i;
	int result[26] = {0};
	FILE* fp = fopen(_fileName, "r");
	if(!fp)
	{
		return 1;
	}
	while((c = fgetc(fp)) != EOF)
	{
		if(65 <= c && c <= 90)
		{
			result[ c- 65]++;
		}
		if(97 <= c && c <= 122)
		{
			result[c - 97]++;
		}
	}
	for(i = 0; i < 26; i++)
	{
		printf("%c occurs %d times\n", (char)(i + 65), result[i]);
	}
	return 0;
}

int WordFreq(char* _fileName)
{
	FILE* fp = fopen(_fileName, "r");
	if(!fp)
	{
		return 1;
	}
	
	
	return 0;
}
