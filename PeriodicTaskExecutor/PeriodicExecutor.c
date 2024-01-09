#include "PeriodicExecutor.h"
#include "Task.h"
#include "../Generics/Heap/genHeap.h"
#include "../Generics/Vector/genVector.h"
#include <stdlib.h> /*malloc*/
#include <string.h> /*strcpy*/
#include <time.h>/* time MACROS*/

#define NAMESIZE 32
#define MAGICNUM 56456534
#define ARBITRARY_INITIALIZATION_VLUE 4

struct PeriodicExecutor
{
    char m_name[NAMESIZE];
    clockid_t m__clk_id;
    Vector* m_tasks;
    int m_isPaused;
    int m_magicNum;
};

static int PauseTask(void* _context);

PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clk_id)
{
    PeriodicExecutor* executor = NULL;
    if(!_name || !_clk_id || !(_clk_id == CLOCK_MONOTONIC || _clk_id == CLOCK_REALTIME || _clk_id == CLOCK_REALTIME_COARSE))
    {
        return NULL;
    }
    executor = malloc(sizeof(PeriodicExecutor));
    if(!executor)
    {
        return executor;
    }
    strcpy(executor->m_name, _name);
    executor->m_tasks = VectorCreate(ARBITRARY_INITIALIZATION_VLUE, ARBITRARY_INITIALIZATION_VLUE);
    executor->m_isPaused = 0;
    executor->m__clk_id = _clk_id;
    executor->m_magicNum = MAGICNUM;
    return executor;
}

void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{
    if(!_executor)
    {
        return;
    }
    if(_executor->m_magicNum == MAGICNUM)
    {
        VectorDestroy(&_executor->m_tasks, TaskDestroy);
        _executor->m_magicNum = 0;
        free(_executor);
    }
}

int PeriodicExecutorAdd(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _period_ms)
{
    Task* task = NULL;
    if(!_executor || !_taskFunction || !_period_ms)
    {
        return 0;
    }
    task = TaskCreate(_taskFunction, _period_ms, _context, 0);
    HandleVectorResult(VectorAppend(_executor->m_tasks, (void*)task));
    return 1;
}

size_t PeriodicExecutorRun(PeriodicExecutor* _executor)
{
    Task* task = NULL;
    Heap* heap = NULL;
    size_t counter = 0;
    if(!_executor)
    {
        return 0;
    }
    heap = HeapBuild(_executor->m_tasks, TaskComperator);
    _executor->m_isPaused = 0;
    while(!_executor->m_isPaused)
    {
        task = (Task*)HeapExtract(heap);
        if(!task)
        {
            puts("trying to execute NULL task");
            return counter;
        }
        if(!TaskRun(task))
        {
            TaskUpdateInterval(task, _executor->m__clk_id);
            HeapInsert(heap, (void*)task);
        }
        counter++;
    }
    HeapDestroy(&heap);
    return counter;
}
/*
size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
    if(!_executor)
    {
        return 0;
    }
    VectorAppend(_executor->m_tasks, TaskCreate(PauseTask, 1, (void*)_executor, 1));
    return VectorSize(_executor->m_tasks);
}

int PauseTask(void* _context)
{
    puts("pausing Executor");
    ((PeriodicExecutor*)_context)->m_isPaused = 1;
    return 1;
}
*/
size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
    if(!_executor)
    {
        return 0;
    }
    _executor->m_isPaused = 1;
    return VectorSize(_executor->m_tasks);
}