#include "linkedPerson.h"
#include <stdlib.h>


int main(void)
{
	FILE* fp = fopen("binary", "w+");
	Person subs[]={{10, "Moshe", 34, NULL}, 
				   {20, "David", 21, NULL}, 
				   {30, "Izhak", 67, NULL}, 
				   {40, "Yakov", 80, NULL}, 
				   {50, "Yosef", 12, NULL}};
	Person* third = malloc(sizeof(Person));
	/*
	Person* item = NULL;
	Person* last = NULL;
	Person* myHead = ListInsertHead(NULL , &subs[0]);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListInsertHead(myHead , &subs[1]);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListRemoveHead(myHead, &item);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListInsertByKey(myHead, subs[2].m_id, &subs[2]);
	PrintList(myHead);
	printf("----------------\n");
	item->m_next = NULL;
	myHead = ListInsertByKeyRec(myHead, item->m_id, item);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListInsertByKeyRec(myHead, subs[3].m_id, &subs[3]);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListRemoveByKey(myHead, 30, &item);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListInsertByKeyRec(myHead, item->m_id, item);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListInsertByKeyRec(myHead, subs[4].m_id, &subs[4]);
	PrintList(myHead);
	printf("----------------\n");
	myHead = ListRemoveByKeyRec(myHead, 50, &item);
	PrintList(myHead);
	printf("----------------\n");
	last = LastNodeRec(myHead);
	printf("%s age:%d, ID:%d\n", last->m_name, last->m_age, last->m_id);
	printf("----------------\n");
	myHead = ListInsertByKeyRec(myHead, item->m_id, item);
	PrintList(myHead);
	printf("----------------\n");
	item = OldestPersonRec(myHead);
	printf("%s age:%d, ID:%d\n", item->m_name, item->m_age, item->m_id);
	
	List* lst = ListCreate();
	ListPrint(lst);
	ListPushHead(lst, 4);
	ListPrint(lst);
	ListPushHead(lst, 40);
	ListPrint(lst);
	ListDestroy;
	*/
	
	fwrite(subs, sizeof(Person), sizeof(subs)/sizeof(Person), fp);
	fseek(fp, sizeof(Person) * 2, SEEK_SET);
	fread(third, sizeof(Person), 1, fp);
	printf("%s age:%d, ID:%d\n", third->m_name, third->m_age, third->m_id);
	return 0;
}
