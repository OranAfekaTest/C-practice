#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ADTVect.h"
#include "ADTDefs.h"

void FontColor(int r, int g, int b)
{
/*    char color[20] = */
    printf("\e[38;2;%d;%d;%dm",r,g,b);/* 200;0;0m";*/
}
void ColorReset()
{
    printf("\x1b[0m");
}
void Pass()
{
	FontColor(0,200,0);
	printf("Pass\n");
	ColorReset();
}
void Fail()
{
	FontColor(200,0,0);
	printf("Fail\n");
	ColorReset();
}

/*** Vector* VectorCreate (size_t _initialSize, size_t _extensionBlockSize);***/
/* _initialSize			_extensionBlockSize 	result
    0					0						NULL
	-1					0						NULL
	0					5						!NULL
	5					0						!NULL
	10					5						if(_vector){
														_vector->m_blockSize == 5
														_vector->m_nItems == 0
														_vector->m_items != NULL;
														_vector->m_originalSize = 10
														_vector->m_size == 10
														_vector->m_magicNumber == MAGIC_NUMBER
														}
*/
void testVectorCreate()
{
	Vector *zero_size;
	Vector *zero_block;
	Vector *zero_both;
	Vector *legitPtr_block_size_5;
	Vector *legitPtr_block_size_TOO_BIG;
	
	printf("testing vectorCreate...\n");
	
	printf("\ntesting _initialSize = 0, _extensionBlockSize = 5...");
	zero_size = VectorCreate(0,5);
	if(zero_size && getMagicNumber(zero_size) == MAGIC_NUMBER){
			Pass();
	}
	else{
		Fail();
	}
	
	printf("\ntesting _initialSize = 5, _extensionBlockSize = 0...");
	zero_block = VectorCreate(5,0);
	if(zero_block && getMagicNumber(zero_block) == MAGIC_NUMBER){
			Pass();
	}
	else{
		Fail();
	}
	
	printf("\ntesting _initialSize = 0, _extensionBlockSize = 0...");
	zero_both = VectorCreate(0,0);
	if(zero_both){
		Fail();
	}
	else{
		Pass();
	}
	
	printf("\ntesting _initialSize = 2, _extensionBlockSize = 5...");
	legitPtr_block_size_5 = VectorCreate(2,5);
	if(legitPtr_block_size_5 && getMagicNumber(legitPtr_block_size_5) == MAGIC_NUMBER){
			Pass();
			printf("Testing Parameters...\n");
			
			printf("Testing block_size...");
			if(getBlockSize(legitPtr_block_size_5) == 5){
				Pass();
			}
			else{
				Fail();
			}
			
			printf("Testing m_nItems...");
			if(getNumberOfItems(legitPtr_block_size_5) == 0){
				Pass();
			}
			else{
				Fail();
			}
			
			printf("Testing m_items...");
			if(getItems(legitPtr_block_size_5)){
				Pass();
			}
			else{
				Fail();
			}
			
			printf("Testing m_originalSize...");
			if(getOrigSize(legitPtr_block_size_5) == 2){
				Pass();
			}
			else{
				Fail();
			}
			
			printf("Testing m_size...");
			if(getSize(legitPtr_block_size_5) == 2){
				Pass();
			}
			else{
				Fail();
			}
	}
	else{
		Fail();
	}
	
	printf("\ntesting _initialSize = 2, _extensionBlockSize = -1...");
	legitPtr_block_size_TOO_BIG = VectorCreate(2,-1);
		if(legitPtr_block_size_TOO_BIG && getMagicNumber(legitPtr_block_size_TOO_BIG) == MAGIC_NUMBER){
			Pass();
	}
	else{
		Fail();
	}
	VectorDestroy(zero_size);
	VectorDestroy(zero_block);
	VectorDestroy(legitPtr_block_size_5);
	VectorDestroy(legitPtr_block_size_TOO_BIG);
}

/*** void VectorDestroy(Vector* _vector); ***/
/* 	we send				result
   	_vector				if(_vector == NULL){OK}
			    		if(_vector != NULL) _vector->m_magicNumber != MAGIC_NUMBER
	NULL				Pass
	((Ptr) not legit))	if(*Vector == NULL)		{Vector *Ptr;  <= we scope}
	
	VectorDestroy(*_vector (legit)) &&	VectorDestroy(*_vector)			OK 	Check for double free	
	
*/
void testVectorDestroy()
{
	Vector *legitPtr_block_size_5;
	legitPtr_block_size_5 = VectorCreate(2,5);
	printf("testing vectorDestroy...\n");

	
	printf("\ntesting destroy once...");
	
	VectorDestroy(legitPtr_block_size_5);
	if(!legitPtr_block_size_5){
			Pass();
	}
	else{
		if(getMagicNumber(legitPtr_block_size_5) != MAGIC_NUMBER){
			Pass();
		}
		else{
			Fail();
		}
	}
	printf("Testing double free...");
	VectorDestroy(legitPtr_block_size_5);
	if(!legitPtr_block_size_5){
			Pass();
	}
	else{
		if(getMagicNumber(legitPtr_block_size_5) != MAGIC_NUMBER){
			printf("Pass magic number deletion\n");
		}
		else{
			Fail();
		}
	}
	

	printf("Testing NULL pointer...");
	VectorDestroy(NULL);
	Pass();	
}




/*** ADTErr VectorAdd(Vector *_vector, int _item); ***/
/*_vector		_item
  NULL Ptr		num ok			error pointer null
	legit		any number		OK
	
Two cases: Without realloc:
adding less m_size{ 		
		if(_vector){
			_vector->m_blockSize == 5						same
			_vector->m_nItems == 0     						got bigger
			_vector->m_items != NULL;						_vector->m_items[_vector->m_nItems-1] == item;
			_vector->m_originalSize = 10					same
			_vector->m_size == 10							same
			_vector->m_magicNumber == MAGIC_NUMBER
		}
		
With realloc:
adding more or equal m_size{ 		
		if(_vector){
			_vector->m_blockSize == {5 / 0 / -1}			{ok, ERR_OVERFLOW, ERR_REALLOCATION_FAILED}		if ERR_REALLOCATION_FAILED && data ok	
			_vector->m_nItems 						== 		got bigger by number items added
			_vector->m_items[_vector->m_nItems-1] 	== 		item;  //PERSONAL CODE DEPENDENT
			_vector->m_originalSize 				==		same
			_vector->m_size 						==		+= m_blockSize
		}
*/
/* Add item to end. */
void testVectorAdd()
{
	Vector *vec_block_size_5 = VectorCreate(2,5);
	Vector *vec_block_size_0 = VectorCreate(2,0);
	Vector *vec_block_size_TOO_BIG = VectorCreate(2,-1);
	int err_res, i, tmpI;
	
	printf("Testing VectorAdd...\n");
	printf("Testing Vector Pointer NULL...");
	err_res = VectorAdd(NULL, 3);
	if(err_res == ERR_NOT_INITIALIZED){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	
	printf("Testing Vector Addition without reallocation...\n");
	printf("Testing Vector blocksize == 5...\n");
	err_res = VectorAdd(vec_block_size_5, 3);
	if(err_res == ERR_OK){
		Pass();
		printf("Testing added correctly...");
		if((getBlockSize(vec_block_size_5) == 5) &&
			(getNumberOfItems(vec_block_size_5) == 1) &&
			(getOrigSize(vec_block_size_5) == 2) &&
			(getSize(vec_block_size_5) == 2) &&
			(getItem(vec_block_size_5,0) == 3)){
				Pass();
		}
		else{
			Fail();
		}
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	printf("Testing Vector blocksize == 0...\n");
	err_res = VectorAdd(vec_block_size_0, 3);
	if(err_res == ERR_OK){
		Pass();
		printf("Testing added correctly...");
		if((getBlockSize(vec_block_size_0) == 0) &&
			(getNumberOfItems(vec_block_size_0) == 1) &&
			(getOrigSize(vec_block_size_0) == 2) &&
			(getSize(vec_block_size_0) == 2) &&
			(getItem(vec_block_size_0,0) == 3)){
				Pass();
		}
		else{
			Fail();
		}
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	printf("Testing Vector Addition with reallocation...\n");
	tmpI = getSize(vec_block_size_5)+5;
	printf("Testing Vector blocksize == 5... adding %d items\n",tmpI);
	for(i=1; i < tmpI; i++){
		if(i > 10)break;
		printf("Adding %d to position %d...",i,i);
		err_res = VectorAdd(vec_block_size_5, i);
		
		if(err_res != ERR_OK){
			Fail();
			break;
		}
		else{
			Pass();
		}
	}
	if(err_res == ERR_OK){
		Pass();
		printf("Testing added correctly...");
		if(getBlockSize(vec_block_size_5) != 5)printf("block size changed\n"); 
		if(getNumberOfItems(vec_block_size_5) != tmpI){
			printf("error number of items. got %d instead of %d\n",getNumberOfItems(vec_block_size_5),(getSize(vec_block_size_5)+6));
		}
		if(getOrigSize(vec_block_size_5) != 2)printf("original size changed\n");
		if(getSize(vec_block_size_5) != getOrigSize(vec_block_size_5)+getBlockSize(vec_block_size_5)){
			printf("error new size. got %d instead of %d\n",getSize(vec_block_size_5),(getOrigSize(vec_block_size_5)+getBlockSize(vec_block_size_5)));
		}
		for(i = 1; i < tmpI; i++){
				if(getItem(vec_block_size_5,i) != i){
					printf("Failed data in item #%d, got %d instead of %d\n",i,getItem(vec_block_size_5,i),i);
					err_res = ERR_GENERAL;
				}
		}
		if(err_res == ERR_OK){
			Pass();
		}
		else{
			Fail();
			HandleErr(err_res, "got this instead\n");
		}
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	
	
	tmpI = getSize(vec_block_size_0)+3;
	printf("Testing Vector blocksize == 0... adding %d items\n",tmpI);
	for(i=1; i < tmpI; i++){
		printf("Adding %d to position %d...",i,i);
		err_res = VectorAdd(vec_block_size_0, i);
		if(getNumberOfItems(vec_block_size_0) <= 2 && i == 1){
			if(err_res == ERR_OK){
				Pass();
			}
			else{
				HandleErr(err_res, "failed here\n");
			}
		}
		else{
			if(err_res != ERR_OVERFLOW){
				HandleErr(err_res, "equal fail\n");
			}
			else{
				Pass();
			}
		}

	}
	printf("Testing All parameters good...");
	if((getBlockSize(vec_block_size_0) == 0) &&
		(getNumberOfItems(vec_block_size_0) == 2) &&
		(getOrigSize(vec_block_size_0) == 2) &&
		(getSize(vec_block_size_0) == 2)){
		Pass();
	}
	
	tmpI = getSize(vec_block_size_TOO_BIG)+3;
	printf("Testing Vector reallocation fail safe...\n");
	printf("Adding less items than size...");
	err_res = VectorAdd(vec_block_size_TOO_BIG, 0);
	if(err_res == ERR_OK){
		Pass();
	}
	else{
		HandleErr(err_res, "failed here\n");
	}
	err_res = VectorAdd(vec_block_size_TOO_BIG, 1);
	if(err_res == ERR_OK){
		Pass();
	}
	else{
		HandleErr(err_res, "failed here\n");
	}
	printf("Testing reallocation failour...");
	err_res = VectorAdd(vec_block_size_TOO_BIG, 2);
	if(err_res == ERR_REALLOCATION_FAILED){
		Pass();
	}
	else{
		
		HandleErr(err_res, "failed here\n");
	}

	printf("Testing All parameters good...");
	tmpI = ERR_OK;
	if(getBlockSize(vec_block_size_TOO_BIG) != -1){
		printf("error block size. got:%u\n",getBlockSize(vec_block_size_TOO_BIG)); 
		tmpI = ERR_GENERAL;
	}
	if(getNumberOfItems(vec_block_size_TOO_BIG) != 2){
			printf("error number of items. got %d instead of %d\n",getNumberOfItems(vec_block_size_TOO_BIG),2);
			tmpI = ERR_GENERAL;
		}
	if(getOrigSize(vec_block_size_TOO_BIG) != 2){
		printf("original size changed. got:%u\n",getOrigSize(vec_block_size_TOO_BIG));
		tmpI = ERR_GENERAL;
	}
	if(getSize(vec_block_size_TOO_BIG) != 2){
		printf("error new size. got %u instead of 2\n",getSize(vec_block_size_TOO_BIG));
		tmpI = ERR_GENERAL;
	}
	if(tmpI == ERR_OK){
			Pass();
	}
	else{
		Fail();
	}
	
	printf("destroy vec_5\n");
	VectorDestroy(vec_block_size_5);
	printf("destroy vec_0\n");
	VectorDestroy(vec_block_size_0);
	printf("destroy vec_block_size_TOO_BIG \n");
	VectorDestroy(vec_block_size_TOO_BIG);
	
}
/*** ADTErr VectorDelete(Vector *_vector, int* _item); ***/
/*_vector		_item
  NULL Ptr		num ok			error pointer null
  legit			NULL			ERR_ITEM_POINTER
	legit		legit			OK
	
Two cases: Without realloc:
deleting less than m_nItems{ 		
			if(_vector){
				_vector->m_blockSize 						==		same
				_vector->m_nItems       					==		got smaller by deletion size
				_vector->m_items  							==		{!= NULL && _vector->m_items[_vector->m_nItems-1] == last item;}
				_vector->m_originalSize  					==		same
				_vector->m_size  							==		same
			}
		
With realloc:
deleting more or equal BLOCK_SIZE_BUFFER * m_blockSize{ 		
			if(_vector){
				_vector->m_blockSize  = {5 / 0 / -1}	==		{ok, ERR_UNDERFLOW, ERR_REALLOCATION_FAILED}		if ERR_REALLOCATION_FAILED && data ok	
				_vector->m_nItems 						== 		got smaller by number items deleted
				_vector->m_items[_vector->m_nItems-1] 	== 		item;  //PERSONAL CODE DEPENDENT
				_vector->m_originalSize 				==		same
				_vector->m_size 						==		-= m_blockSize
			}
			
 ==> 	Also try to decrease more than m_originalSize <==

*/
/* Delete item from the end. */
void testVectorDelete()
{
	Vector *vec_block_size_5 = VectorCreate(2,5);
	Vector *vec_block_size_0 = VectorCreate(2,0);
	int err_res, i, tmpItem, tmpI;
	size_t bs,nI,os,s;
	
	printf("Testing VectorDelete...\n");
	printf("Testing Vector Pointer NULL...");
	err_res = VectorDelete(NULL, &tmpItem);
	if(err_res == ERR_NOT_INITIALIZED){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	printf("Testing Item Pointer NULL...");
	err_res = VectorDelete(vec_block_size_5, NULL);
	if(err_res == ERR_ITEM_POINTER){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	printf("Testing Item and vector legit...");
	VectorAdd(vec_block_size_5,10);
	err_res = VectorDelete(vec_block_size_5, &tmpItem);
	if(err_res == ERR_OK && tmpItem == 10){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing empty stack ...");
	err_res = VectorDelete(vec_block_size_5, &tmpItem);
	if(err_res == ERR_STACK_EMPTY){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	for(i=0;i<10;i++){
		VectorAdd(vec_block_size_5,i);
	}
	bs = getBlockSize(vec_block_size_5);
	nI = getNumberOfItems(vec_block_size_5);
	os = getOrigSize(vec_block_size_5);
	s =  getSize(vec_block_size_5);
	printf("Testing deletion without realloc ...");
	err_res = VectorDelete(vec_block_size_5, &tmpItem);
	if(err_res == ERR_OK && tmpItem == 9){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	printf("Testing All parameters good...");
	tmpI = ERR_OK;
	if(getBlockSize(vec_block_size_5) != bs){
		printf("error block size. got:%u\n",getBlockSize(vec_block_size_5)); 
		tmpI = ERR_GENERAL;
	}
	if(getNumberOfItems(vec_block_size_5) != (nI-1)){
			printf("error number of items. got %d instead of %d\n",getNumberOfItems(vec_block_size_5),10);
			tmpI = ERR_GENERAL;
		}
	if(getOrigSize(vec_block_size_5) != os){
		printf("original size changed. got:%u\n",getOrigSize(vec_block_size_5));
		tmpI = ERR_GENERAL;
	}
	if(getSize(vec_block_size_5) != s){
		printf("error new size. got %u instead of 2\n",getSize(vec_block_size_5));
		tmpI = ERR_GENERAL;
	}
	if(tmpI == ERR_OK){
			Pass();
	}
	else{
		Fail();
	}
	
	for(i=9;i<30;i++){
		VectorAdd(vec_block_size_5,i);
	}
	bs = getBlockSize(vec_block_size_5);
	nI = getNumberOfItems(vec_block_size_5);
	os = getOrigSize(vec_block_size_5);
	s =  getSize(vec_block_size_5);
	printf("Testing deletion with realloc ...");
	for(i=29;i>1;i--){
		err_res = VectorDelete(vec_block_size_5, &tmpItem);
	}
	if(err_res == ERR_OK && tmpItem == 2){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	
	printf("Testing All parameters good...");
	tmpI = ERR_OK;
	if(getBlockSize(vec_block_size_5) != bs){
		printf("error block size. got:%u\n",getBlockSize(vec_block_size_5)); 
		tmpI = ERR_GENERAL;
	}
	if(getNumberOfItems(vec_block_size_5) != 2){
			printf("error number of items. got %d instead of %d\n",getNumberOfItems(vec_block_size_5),2);
			tmpI = ERR_GENERAL;
		}
	if(getOrigSize(vec_block_size_5) != os){
		printf("original size changed. got:%u\n",getOrigSize(vec_block_size_5));
		tmpI = ERR_GENERAL;
	}
	if(getSize(vec_block_size_5)  != 12){
		printf("error new size. got %u instead of 2\n",getSize(vec_block_size_5));
		tmpI = ERR_GENERAL;
	}
	if(tmpI == ERR_OK){
			Pass();
	}
	else{
		Fail();
	}
	printf("Testing deletion more  than original size...");
	Vector *vec_block_size_1 = VectorCreate(1,1);
	for(i=0;i<5;i++){
		VectorAdd(vec_block_size_1,i);

	}
	for(i=5;i>0;i--){
		err_res = VectorDelete(vec_block_size_1, &tmpItem);
		if(err_res == ERR_OK && tmpItem == (i-1)){
			printf(".");
		}
		else{
			printf("Failed. last item:%d\n",tmpItem);
			HandleErr(err_res, "got this instead\n");
		}
	}
	if((getOrigSize(vec_block_size_1)+getBlockSize(vec_block_size_1)) == getSize(vec_block_size_1)){
		Pass();
	}
	else{
				printf("error. size %u .  original %u\n",getSize(vec_block_size_1), getOrigSize(vec_block_size_1));
	}
	printf("destroy vec_5\n");
	VectorDestroy(vec_block_size_5);
	printf("destroy vec_0\n");
	VectorDestroy(vec_block_size_0);
	printf("destroy vec_block_size_1 \n");
	VectorDestroy(vec_block_size_1);
}

/* The Index range in the following functions is : 0..numOfItems-1 */
/*** ADTErr VectorGet(Vector *_vector, size_t _index, int *_item); ***/
/*
1) Only Create and try to Get  						==> ERR_WRONG_INDEX
2) Vector ok and i got  correct item by index		==> ERR_OK
3) Vector Ok and try to get (_index == m_nItems)	==> ERR_WRONG_INDEX
	_vector		_index		_item

  NULL Ptr		num ok				error pointer null
  legit			NULL				ERR_ITEM_POINTER
	legit		legit				OK
*/
void testVectorGet()
{
	Vector *vec_block_size_5 = VectorCreate(2,5);
	int err_res, i, tmpItem;
	size_t bs,nI,os,s;
	VectorAdd(vec_block_size_5,10);
	printf("Testing VectorGet...\n");
	printf("Testing Vector Pointer NULL...");
	err_res = VectorGet(NULL, 0, &tmpItem);
	if(err_res == ERR_NOT_INITIALIZED){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing Item Pointer NULL...");
	err_res = VectorGet(vec_block_size_5,0, NULL);
	if(err_res == ERR_ITEM_POINTER){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing legit parameters...");
	err_res = VectorGet(vec_block_size_5,0, &tmpItem);
	if(err_res == ERR_OK){
		Pass();
		if(tmpItem == 10)Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing index == nItems...");
	err_res = VectorGet(vec_block_size_5,1, &tmpItem);
	if(err_res == ERR_WRONG_INDEX){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	Vector *vec_block_size_1 = VectorCreate(1,1);
	printf("Testing empty Vector...");
	err_res = VectorGet(vec_block_size_1, 0, &tmpItem);
	if(err_res == ERR_STACK_EMPTY){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("destroy vec_5\n");
	VectorDestroy(vec_block_size_5);
	printf("destroy vec_block_size_1 \n");
	VectorDestroy(vec_block_size_1);
}
/*** ADTErr VectorSet(Vector *_vector, size_t _index, int _item); ***/
void testVectorSet()
{
	Vector *vec_block_size_5 = VectorCreate(2,5);
	int err_res, i, tmpItem;
	size_t bs,nI,os,s;
	VectorAdd(vec_block_size_5,10);
	printf("Testing VectorSet...\n");
	printf("Testing Vector Pointer NULL...");
	err_res = VectorSet(NULL, 0, 1);
	if(err_res == ERR_NOT_INITIALIZED){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing Item Pointer NULL...");
	err_res = VectorSet(vec_block_size_5,0, NULL);
	if(err_res == ERR_OK){
		Pass();
		VectorGet(vec_block_size_5,0,&tmpItem);
		if(tmpItem == 0)Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing legit parameters...");
	err_res = VectorSet(vec_block_size_5,0, 55);
	if(err_res == ERR_OK){
		Pass();
		VectorGet(vec_block_size_5,0,&tmpItem);
		if(tmpItem == 55)Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing index == nItems...");
	err_res = VectorSet(vec_block_size_5,1, 100);
	if(err_res == ERR_WRONG_INDEX){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	Vector *vec_block_size_1 = VectorCreate(1,1);
	printf("Testing empty Vector...");
	err_res = VectorSet(vec_block_size_1, 0, 99);
	if(err_res == ERR_WRONG_INDEX){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("destroy vec_5\n");
	VectorDestroy(vec_block_size_5);
	printf("destroy vec_block_size_1 \n");
	VectorDestroy(vec_block_size_1);
}
/*** ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems); ***/
void testVectorItemsNum()
{
	Vector *vec_block_size_5 = VectorCreate(2,5);
	size_t err_res, i, tmpItem;
	VectorAdd(vec_block_size_5,10);
	printf("Testing VectorItemsNum...\n");
	printf("Testing Vector Pointer NULL...");
	err_res = VectorItemsNum(NULL,&tmpItem);
	if(err_res == ERR_NOT_INITIALIZED){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing Item Pointer NULL...");
	err_res = VectorItemsNum(vec_block_size_5, NULL);
	if(err_res == ERR_ITEM_POINTER){
		Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("Testing legit parameters...");
	err_res = VectorItemsNum(vec_block_size_5,&tmpItem);
	if(err_res == ERR_OK){
		Pass();
		if(tmpItem == 1)Pass();
	}
	else{
		Fail();
		HandleErr(err_res, "got this instead\n");
	}
	printf("destroy vec_5\n");
	VectorDestroy(vec_block_size_5);
}
/* Unit-Test functions */
void testVectorPrint()
{
	Vector *vec_block_size_5 = VectorCreate(2,5);
	int err_res, i, tmpItem;
	
	printf("Testing VectorPrint...\n");
	printf("Testing Vector Pointer NULL...");
	VectorPrint(NULL);
	Pass();
	printf("Testing Vector Empty...");
	VectorPrint(vec_block_size_5);
	Pass();
	VectorAdd(vec_block_size_5,10);
	printf("Testing Vector with item == 10...");
	VectorPrint(vec_block_size_5);
	Pass();
	printf("destroy vec_5\n");
	VectorDestroy(vec_block_size_5);
}
/*** void VectorPrint(Vector *_vector); ***/
/* _vector is NULL ==> not getting segmentation fault */



/*better to have each test by it's own function */
void testStackCreate()
{
	Stack *s, *legit_stack, *null_blocksize;
	int i,_item;
	printf("Testing StackCreate...\n");
	printf("Testing NULL _size...");
	s = StackCreate(NULL,5);
	if(s){
		Pass();
	}
	else{
		Fail();
	}
	StackDestroy(s);
	printf("Testing NULL _blockSize...");
	null_blocksize = StackCreate(5,NULL);
	if(null_blocksize){
		Pass();
	}
	else{
		Fail();
	}
	StackDestroy(null_blocksize);	
	
	printf("Testing size & blockSize NULL...");
	legit_stack = StackCreate(0,0);
	if(legit_stack){
		Fail();
	}
	else{
		Pass();
	}	
	printf("Testing parameters legit...");
	
	legit_stack = StackCreate(5,5);
	if(legit_stack){
		Pass();
		StackDestroy(legit_stack);
	}
	else{
		Fail();
	}		

}

void testStackDestroy()
{
	Stack *stack_uninitialized, *double_destroy;
	int i,_item;
	printf("Testing StackDestroy...\n");
	
	printf("Testing Uninitialized Stack...");
	StackDestroy(stack_uninitialized);
	Pass();
	
	printf("Testing NULL Stack...");
	StackDestroy(NULL);
	Pass();
	printf("Testing legit Stack...");
	double_destroy = StackCreate(10,10);
	StackDestroy(double_destroy);
	Pass();	
	printf("Testing double destroy Stack...");
	StackDestroy(double_destroy);
	Pass();

}

void testStackPush()
{
	Stack *stack_uninitialized, *stack_destroyed, *stack_null_item, *stack_block_size_huge, *stack_normal, *stack_block_size_0;
	int i,_item = 0, result;
	int dataOk;
	printf("Testing StackPush...\n");
	
	
	printf("Testing Uninitialized Stack...");
	if((result = StackPush(stack_uninitialized,_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	stack_destroyed = StackCreate(10,10);
	StackDestroy(stack_destroyed);
	printf("Testing stack_destroyed...");
	if((result = StackPush(stack_destroyed,_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	printf("Testing NULL stack...");
	if((result = StackPush(NULL,_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	stack_null_item = StackCreate(10,10);
	printf("Testing stack_null_item...");
	if((result = StackPush(stack_null_item,NULL)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		Pass();
	}
	StackDestroy(stack_null_item);
	stack_block_size_0 = StackCreate(1,0);
	printf("Testing stack_block_size_0...");
	if((result = StackPush(stack_block_size_0,0)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		Pass();
	}
	printf("Testing stack over_flow...");
	StackPush(stack_block_size_0,13);
	
	if((result = StackPush(stack_block_size_0,13)) != ERR_OVERFLOW){
		Fail();
		HandleErr(result,"should be ERR_OVERFLOW\n");
	}
	else{
		Pass();
	}
	
	StackDestroy(stack_block_size_0);
	stack_block_size_huge = StackCreate(1,-3);
	printf("Testing stack_block_size_huge without realloc...");
	if((result = StackPush(stack_block_size_huge,0)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		Pass();
	}
	printf("Testing stack_block_size_huge with realloc...");
	StackPush(stack_block_size_huge,13);
	
	if((result = StackPush(stack_block_size_huge,13)) != ERR_REALLOCATION_FAILED){
		Fail();
		HandleErr(result,"should be ERR_REALLOCATION_FAILED\n");
	}
	else{
		Pass();
	}
	printf("Testing values pushed...");
	if((result = StackTop(stack_block_size_huge, &_item)) == ERR_OK){
		if(_item == 0){
			Pass();
		}
		else{
			Fail();
		}
	}
	StackDestroy(stack_block_size_huge);
	stack_normal = StackCreate(2,5);
	printf("Testing stack normal - multyple push...");
	dataOk = 1;
	for(i=0; i<20; i++){
		if((result = StackPush(stack_normal,i)) != ERR_OK){
			Fail();
			HandleErr(result,"should be ERR_OK\n");
			dataOk = 0;
		}
	}
	if(dataOk){
		Pass();
	}
	dataOk = 1;
	for(i=19; i>=0; i--){
		if((result = StackPop(stack_normal,&_item)) != ERR_OK){
			Fail();
			HandleErr(result,"should be ERR_OK\n");
			dataOk = 0;
		}
		if(_item != i){
			Fail();
			dataOk = 0;
		}
	}
	printf("Testing stack normal - multyple push values...");
	if(dataOk){
		Pass();
	}
	StackDestroy(stack_normal);

}
void testStackPop()
{
	Stack *stack_uninitialized, *stack_destroyed, *stack_null_item, *stack_normal, *stack_block_size_1;
	int i,_item = 0, result;
	int dataOk;
	printf("Testing StackPop...\n");
	
	
	printf("Testing Uninitialized Stack...");
	if((result = StackPop(stack_uninitialized,&_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	stack_destroyed = StackCreate(10,10);
	StackDestroy(stack_destroyed);
	printf("Testing stack_destroyed...");
	if((result = StackPop(stack_destroyed,&_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	printf("Testing NULL stack...");
	if((result = StackPop(NULL,&_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	stack_null_item = StackCreate(10,10);
	printf("Testing stack_null_item...");
	StackPush(stack_null_item,NULL);
	if((result = StackPop(stack_null_item,&_item)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		if(_item == 0 && StackIsEmpty(stack_null_item)){
			Pass();
		}
		else{
			Fail();
		}
	}
	StackDestroy(stack_null_item);
	
	stack_block_size_1 = StackCreate(0,1);
	printf("Testing stack size == 0; stack_block_size == 1...");
	StackPush(stack_block_size_1,99);
	if((result = StackPop(stack_block_size_1,&_item)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		if(_item == 99 && StackIsEmpty(stack_block_size_1)){
			Pass();
		}
		else{
			Fail();
		}
	}
	printf("Testing stack under_flow...");
	if((result = StackPop(stack_block_size_1,&_item)) != ERR_STACK_EMPTY){
		Fail();
		HandleErr(result,"should be ERR_STACK_EMPTY\n");
	}
	else{
		Pass();
	}
	StackDestroy(stack_block_size_1);
	
	stack_normal = StackCreate(2,5);
	printf("Testing stack normal - multyple pop...");
	dataOk = 1;
	for(i=0; i<20; i++){
		if((result = StackPush(stack_normal,i)) != ERR_OK){
			HandleErr(result,"should be ERR_OK\n");
		}
	}
	dataOk = 1;
	for(i=19; i>=0; i--){
		if((result = StackPop(stack_normal,&_item)) != ERR_OK){
			Fail();
			HandleErr(result,"should be ERR_OK\n");
			dataOk = 0;
		}
		if(_item != i){
			Fail();
			dataOk = 0;
		}
	}
	printf("Testing stack normal - multyple pop values...");
	if(dataOk){
		Pass();
	}	
	StackDestroy(stack_normal);
}

void testStackTop()
{
	Stack *stack_uninitialized, *stack_destroyed, *stack_null_item, *stack_normal, *stack_block_size_1;
	int i,_item = 0, result;
	int dataOk;
	printf("Testing StackTop...\n");
	
	
	printf("Testing Uninitialized Stack...");
	if((result = StackTop(stack_uninitialized,&_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	stack_destroyed = StackCreate(10,10);
	StackDestroy(stack_destroyed);
	printf("Testing stack_destroyed...");
	if((result = StackTop(stack_destroyed,&_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	printf("Testing NULL stack...");
	if((result = StackTop(NULL,&_item)) != ERR_NOT_INITIALIZED){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	stack_null_item = StackCreate(10,10);
	printf("Testing stack_null_item...");
	StackPush(stack_null_item,NULL);
	if((result = StackTop(stack_null_item,&_item)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		if(_item == 0 && !StackIsEmpty(stack_null_item)){
			Pass();
		}
		else{
			Fail();
		}
	}
	StackDestroy(stack_null_item);
	
	stack_block_size_1 = StackCreate(0,1);
	printf("Testing stack size == 0; stack_block_size == 1...");
	StackPush(stack_block_size_1,99);
	if((result = StackTop(stack_block_size_1,&_item)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_OK\n");
	}
	else{
		if(_item == 99 && !StackIsEmpty(stack_block_size_1)){
			Pass();
		}
		else{
			Fail();
		}
	}
	printf("Testing stack under_flow...");
	if((result = StackTop(stack_block_size_1,&_item)) != ERR_OK){
		Fail();
		HandleErr(result,"should be ERR_STACK_EMPTY\n");
	}
	else{
		Pass();
	}
	StackDestroy(stack_block_size_1);
	
	stack_normal = StackCreate(2,5);
	printf("Testing stack normal - multyple pop...");
	dataOk = 1;
	for(i=0; i<20; i++){
		if((result = StackPush(stack_normal,i)) != ERR_OK){
			HandleErr(result,"should be ERR_OK\n");
		}
	}
	dataOk = 1;
	for(i=19; i>=0; i--){
		if((result = StackTop(stack_normal,&_item)) != ERR_OK){
			Fail();
			HandleErr(result,"should be ERR_OK\n");
			dataOk = 0;
		}
		if(_item != 19){
			Fail();
			dataOk = 0;
		}
	}
	printf("Testing stack normal abused values...");
	if(dataOk){
		Pass();
	}	
	StackDestroy(stack_normal);
}
void testStackIsEmpty()
{

	Stack *stack_destroyed, *stack_null_item, *stack_normal, *stack_block_size_1;
	int i,_item = 0, result;

	printf("Testing StackIsEmpty...\n");

	stack_destroyed = StackCreate(10,10);
	StackDestroy(stack_destroyed);
	printf("Testing stack_destroyed...");
	if(StackIsEmpty(stack_destroyed)){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}
	
	printf("Testing NULL stack...");
	if(StackIsEmpty(NULL)){
		Fail();
		HandleErr(result,"should be ERR_NOT_INITIALIZED\n");
	}
	else{
		Pass();
	}

	stack_normal = StackCreate(2,5);
	printf("Testing stack normal - multyple pop...");
	for(i=0; i<20; i++){
		if((result = StackPush(stack_normal,i)) != ERR_OK){
			HandleErr(result,"should be ERR_OK\n");
		}
	}
	for(i=19; i>=0; i--){
		StackPop(stack_normal,&_item);
	}
	if(StackIsEmpty(stack_normal)){
		Pass();
	}
	else{
		Fail();		
	}
}
void testStackPrint()
{
	Stack *stack_destroyed, *stack_null_item, *stack_normal, *stack_block_size_1;
	int i,_item = 0, result;

	printf("Testing StackPrint...\n");

	stack_destroyed = StackCreate(10,10);
	StackDestroy(stack_destroyed);
	printf("Testing stack_destroyed...");
	StackPrint(stack_destroyed);
	Pass();
	
	printf("Testing NULL stack...");
	StackPrint(NULL);
	Pass();

	stack_normal = StackCreate(2,5);
	printf("Testing stack normal - multyple pop...");
	for(i=0; i<20; i++){
		if((result = StackPush(stack_normal,i)) != ERR_OK){
			HandleErr(result,"should be ERR_OK\n");
		}
	}
	StackPrint(stack_normal);
	Pass();
}

