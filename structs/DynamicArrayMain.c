#include "DynamicArray.h"

int main(void)
{
	int i, errorCode;
	DynamicArray* attemp1 = DynamicArrayCreate(0,0);
	DynamicArray* attemp2 = DynamicArrayCreate(0,4);
	DynamicArray* attemp3 = DynamicArrayCreate(4,0);
	DynamicArray* attemp4 = DynamicArrayCreate(4,4);
	
	if(!attemp1)
		printf("attemp1 (0,0) is NULL\n");
	else
		printf("attemp1 (0,0) adress is %p, Array Size = %d, Block Size = %d and the Number Of Elements is %d\n", (void*)attemp1->dArray, attemp1->dArraySize, attemp1->dArrayBlockSize, attemp1->NumOfElements);
	if(!attemp2)
		printf("attemp2 (0,4) is NULL\n");
	else
		printf("attemp2 (0,4) adress is %p, Array Size = %d, Block Size = %d and the Number Of Elements is %d\n", (void*)attemp2->dArray, attemp2->dArraySize, attemp2->dArrayBlockSize, attemp2->NumOfElements);
	if(!attemp3)
		printf("attemp3 (4,0) is NULL\n");
	else
		printf("attemp3 (4,0) adress is %p, Array Size = %d, Block Size = %d and the Number Of Elements is %d\n", (void*)attemp3->dArray, attemp3->dArraySize, attemp3->dArrayBlockSize, attemp3->NumOfElements);
	if(!attemp4)
		printf("attemp3 (4,4) is NULL\n");
	else
		printf("attemp4 (4,4) adress is %p, Array Size = %d, Block Size = %d and the Number Of Elements is %d\n", (void*)attemp4->dArray, attemp4->dArraySize, attemp4->dArrayBlockSize, attemp4->NumOfElements);
	
	for(i = 0; i < 4; i++)
	{
		errorCode = DynamicArrayInsert(attemp2, i);
		printf("%d is inserted to attemp2, Number Of Elements is %d\n", attemp2->dArray[i], attemp2->NumOfElements);
	}
	
	errorCode = DynamicArrayDelete(attemp2, &(attemp2->dArray[2]));
	printf("errorCode od delete %d\n", errorCode);
	for(i = 0; i < 4; i++)
	{
		printf("%d is in attemp2 at %p Number Of Elements is %d\n", attemp2->dArray[i], (void*)&(attemp2->dArray[i]), attemp2->NumOfElements);
	}
	DynamicArrayDestroy(attemp2);
	DynamicArrayDestroy(attemp3);
	DynamicArrayDestroy(attemp4);
	return 0;
}
