#include "genHeap.h"
#define STAM_FACTOR 2

typedef struct Person
{
	int m_id;
	char m_name[128];
	int m_age;
}Person;

Person subs[] = {{10, "Moshe", 34}, 
				 {20, "David", 21}, 
				 {30, "Izhak", 67}, 
				 {40, "Yakov", 80}, 
				 {50, "Yosef", 12},
                 {60, "Shlomo", 24},
                 {70, "Avi", 36},
                 {80, "Haim", 18},
                 {90, "Yair", 92}};

static int PersonComparatorByAge(const void *_left, const void *_right);
static int HeapPrintPerson(const void *_elem, void * _context);
static int VectorPrintPerson(void* _element, size_t _index, void* _context);
static void PrintPerson(Person* _person);

int main(void)
{
    size_t i, size;
    Heap* heap = NULL;
    Vector* vector = NULL;
    size = sizeof(subs)/sizeof(Person);
    vector = VectorCreate(size, STAM_FACTOR);
    for(i = 0; i < size; ++i)
    {
        VectorAppend(vector, &subs[i]);
    }

    VectorForEach(vector, VectorPrintPerson, NULL);
    puts("*********");
    heap = HeapBuild(vector, PersonComparatorByAge);

    HeapForEach(heap, HeapPrintPerson, NULL);
    puts("*********");
    while(0 < HeapSize(heap))
    {
        PrintPerson((Person*)HeapExtract(heap));
    }
    puts("*********");
    HeapDestroy(&heap);
    HeapDestroy(&heap);
    return 0;
}

static int PersonComparatorByAge(const void *_left, const void *_right)
{
    return ((((Person*)_left)->m_age < ((Person*)_right)->m_age) ? 1 : 0);
    
}

static int PersonComparatorById(const void *_left, const void *_right)
{
    return ((((Person*)_left)->m_id < ((Person*)_right)->m_id) ? 1 : 0);
    
}

static void PrintPerson(Person* _person)
{
    if(!_person)
    {
        puts("can't print NULL person.");
        return;
    }
    printf("%s age:%d, ID:%d\n", _person->m_name, _person->m_age, _person->m_id);
}

static int HeapPrintPerson(const void *_elem, void * _context)
{
    Person* person = (Person*)_elem;
    printf("%s age:%d, ID:%d\n", person->m_name, person->m_age, person->m_id);
    return 1;
}

static int VectorPrintPerson(void* _element, size_t _index, void* _context)
{
    Person* person = (Person*)_element;
    printf("%s age:%d, ID:%d\n", person->m_name, person->m_age, person->m_id);
    return 1;
}