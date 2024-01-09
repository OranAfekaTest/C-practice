#ifndef __GENSORT_H__
#define __GENSORT_H__


int GenSort(void* _elements, size_t _elementSize, size_t _size, int(*_criteria)(const void* _a, const void* _b));


#endif /*__GENSORT_H__*/
