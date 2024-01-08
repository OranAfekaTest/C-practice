/* gets:
		getMagicNumber (in main.c)
		
*/

Vector* VectorCreate (size_t _initialSize, size_t _extensionBlockSize);
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
void VectorDestroy(Vector* _vector);
/* 	we send				result
   	_vector				if(_vector == NULL){OK}
			    		if(_vector != NULL) _vector->m_magicNumber != MAGIC_NUMBER
	NULL				Pass
	((Ptr) not legit))	if(*Vector == NULL)		{Vector *Ptr;  <= we scope}
	
	VectorDestroy(*_vector (legit)) &&	VectorDestroy(*_vector)			OK 	Check for double free	
	
*/

ADTErr VectorAdd(Vector *_vector, int _item);
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

ADTErr VectorDelete(Vector *_vector, int* _item);
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

/* The Index range in the following functions is : 0..numOfItems-1 */
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
/*
1) Only Create and try to Get  						==> ERR_WRONG_INDEX
2) Vector ok and i got  correct item by index		==> ERR_OK
3) Vector Ok and try to get (_index == m_nItems)	==> ERR_WRONG_INDEX
	_vector		_index		_item

  NULL Ptr		num ok				error pointer null
  legit			NULL				ERR_ITEM_POINTER
	legit		legit				OK
	


*/

ADTErr VectorSet(Vector *_vector, size_t _index, int _item);

ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems);

/* Unit-Test functions */

void VectorPrint(Vector *_vector);
/* _vector is NULL ==> not getting segmentation fault

