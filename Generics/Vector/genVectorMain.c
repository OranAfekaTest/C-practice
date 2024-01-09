#include "genVector.h"

#define ARBITRARY_INITIAL_SIZE 4

typedef struct Pesron
{
	int m_id;
	char m_name[ARBITRARY_INITIAL_SIZE * ARBITRARY_INITIAL_SIZE];
	int m_age;
}Person;

static void PrintPesrson(Person* _person);
static void EmptyDestroy(void* _item);
static void DestroyPerson(void* _item);
static int	VectorElementAction1(void* _element, size_t _index, void* _context);

Person subs[]={{10, "Moshe", 34}, 
			   {20, "David", 21}, 
			   {30, "Izhak", 67}, 
			   {40, "Yakov", 80}, 
			   {50, "Yosef", 12}};

int main(void)
{
	size_t size, capacity, i;
	VectorResult result;
	struct Pesron* pValue;
	Vector* vec = VectorCreate(0, 0);
	if(!vec)
	{
		puts("VectorCreate(0, 0) pass");
	}
	vec = VectorCreate(0, ARBITRARY_INITIAL_SIZE);
	size = VectorSize(vec);
	capacity = VectorCapacity(vec);
	if(vec)
	{
		printf("VectorCreate(0, 4) pass, size: %ld, capacity: %ld\n", size, capacity);
	}
	result = VectorAppend(vec, &subs[0]);
	if(result != VECTOR_SUCCESS)
	{
		printf("VectorAppend failed\n");
		HandleVectorResult(result);
	}
	size = VectorSize(vec);
	capacity = VectorCapacity(vec);
	
	printf("adding 1 item, size: %ld, capacity: %ld\n", size, capacity);
	
	for(i = 1; i < 5; i++)
	{
		result = VectorAppend(vec, &subs[i]);
		if(result != VECTOR_SUCCESS)
		{
			printf("VectorAppend failed\n");
			HandleVectorResult(result);
		}
	}
	size = VectorSize(vec);
	capacity = VectorCapacity(vec);
	printf("adding 4 items, size: %ld, capacity: %ld\n", size, capacity);

	for(i = 0; i < 6; i++)
	{
		result = VectorRemove(vec, &pValue);
		size = VectorSize(vec);
		capacity = VectorCapacity(vec);
		if(result != VECTOR_SUCCESS)
		{
			puts("VectorRemove failed");
			HandleVectorResult(result);
		}
		else
		{
			printf("size: %ld, capacity: %ld, VectorRemoved person:\n", size, capacity);
			PrintPesrson(pValue);
		}
	}

	VectorDestroy(&vec, EmptyDestroy);
	if(!vec)
	{
		puts("VectorDestroy pass");
	}

	vec = VectorCreate(ARBITRARY_INITIAL_SIZE, 0);
	size = VectorSize(vec);
	capacity = VectorCapacity(vec);
	if(vec)
	{
		printf("VectorCreate(4, 0) pass, size: %ld, capacity: %ld\n", size, capacity);
	}

	for(i = 0; i < 5; i++)
	{
		result = VectorAppend(vec, &subs[i]);
		if(result != VECTOR_SUCCESS)
		{
			puts("VectorAppend more then capacity pass");
			HandleVectorResult(result);
		}
	}
	
	vec = VectorCreate(ARBITRARY_INITIAL_SIZE, ARBITRARY_INITIAL_SIZE);
	size = VectorSize(vec);
	capacity = VectorCapacity(vec);
	if(vec)
	{
		printf("VectorCreate(4, 4) pass, size: %ld, capacity: %ld\n", size, capacity);
	}
	
	

	return 0;
}

void PrintPesrson(Person* _person)
{
	if(!_person)
	{
		return;
	}
	printf("%s age:%d, ID:%d\n", _person->m_name, _person->m_age, _person->m_id);
}

void EmptyDestroy(void* _item)
{

}
void DestroyPerson(void* _item)
{
	free(_item);
}

int	VectorElementAction1(void* _element, size_t _index, void* _context)
{

}