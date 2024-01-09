#include <stdio.h>
#define SIZE_ERROR -1
#define OK 0
#define BY_AGE 1
#define BY_NAME 2

struct Person
{
	int id;
	char name[10];
	int age;
}typedef Person;

int BubbleSort(Person _arr[], int _size, int _comperator);
void PrintArray(Person _arr[], int _size);

int main(void)
{
	int i;
	Person arr[] = {{3123, "koko", 50},{3242, "bobo", 56}, {3142, "momo", 43}};
	int personArrLength = sizeof(arr)/sizeof(Person);
	
	for(i = 0; i < personArrLength; i++)
	{
		printf("Person%d: id = %d, name = %s, age = %d \n", i+1, arr[i].id, arr[i].name, arr[i].age);
	}
	
	
	printf("Sort by age: \n");
	BubbleSort(arr, personArrLength, BY_AGE);
	PrintArray(arr, personArrLength);
	printf("\nSort by name: \n");
	BubbleSort(arr, personArrLength, BY_NAME);
	PrintArray(arr, personArrLength);

	return 0;
}

void Swap(Person _arr[], int _a, int _b)
{
	Person temp = _arr[_a];
	_arr[_a] = _arr[_b];
	_arr[_b] = temp;
}

int BubbleSort(Person _arr[], int _size, int _comperator)
{
	int i, j, flag = 0;
	
	if(_size < 1)
		return SIZE_ERROR;
	
	for(i = 0; i < _size - 1; i++)
	{
		for(j = 0; j < _size - i - 1; j++)
		{
			switch(_comperator)
			{
				case BY_NAME:
					if(strcmp(_arr[j + 1].name, _arr[j].name) < 0)
					{
						Swap(_arr, j, j + 1);
						flag = 1;
					}
					break;
				
				case BY_AGE:
					if(_arr[j + 1].age < _arr[j].age)
					{
						Swap(_arr, j, j + 1);
						flag = 1;
					}
					break;
					
				default:
					if(_arr[j + 1].id < _arr[j].id)
					{
						Swap(_arr, j, j + 1);
						flag = 1;
					}
			}
		}
		if(!flag)
			break;
	}

	return OK;
}

void PrintPerson(Person p)
{
	printf("{name= %s, id= %d, age= %d}\n", p.name, p.id, p.age);
}

void PrintArray(Person _arr[], int _size)
{
	int i;
	putchar('[');
	for(i = 0; i < _size; i++)
	{
		PrintPerson(_arr[i]);
	}
	putchar(']');
	putchar('\n');
}
