#include "Task.h"
#include "CalcTime.h"
#include <stdlib.h> /*malloc*/
#include <stdio.h>/*printf*/
#include <sys/types.h>/*clockid_t*/

#define MAGICNUM 6894235

struct Task
{
    fpTask m_taskFunc;
    size_t m_period_ms;
    /*size_t m_interval;*/
    struct timespec m_nexTime;
    void* m_context;
    int m_magicNum;
    
};

Task* TaskCreate(fpTask _taskFunc, size_t _period_ms, void* _context, int _isPause)
{
    Task* task = NULL;
    static size_t pauseInterval;
    if(!_taskFunc || !_period_ms)
    {
        return NULL;
    }
    task = malloc(sizeof(Task));
    if(!task)
    {
        return NULL;
    }
    pauseInterval += _period_ms;
    task->m_taskFunc = _taskFunc;
    task->m_period_ms = _period_ms;
    task->m_interval = _isPause ? pauseInterval : _period_ms;
    task->m_context = _context;
    task->m_magicNum = MAGICNUM;
    printf("pauseInterval=%ld\n", pauseInterval);
    return task;
}

void TaskDestroy(void* _task)
{
    Task* task = (Task*)_task;
    if(!task)
    {
        return;
    }
    if(task->m_magicNum == MAGICNUM)
    {
        task->m_magicNum = 0;
        free(task);
    }
}

void TaskUpdateInterval(Task* _task, clockid_t _clk_id)
{
    _task->m_interval = GetUpdatedInterval(_task->m_interval, _clk_id);
    /*_task->m_interval += _task->m_period_ms;*/
    printf("%s new interval: %ld\n", (char*)_task->m_context, _task->m_interval);
}

int TaskRun(Task* _task)
{
    if(!_task)
    {
        puts("can't run NULL Task");
        return 0;
    }
    WaitTaskPeriod(_task->m_period_ms);
    printf("%s interval %ld\n", (char*)_task->m_context, _task->m_interval);
    return _task->m_taskFunc(_task->m_context);
}

int TaskComperator(const void* _taskA, const void* _taskB)
{
    if(!_taskA || !_taskB)
    {
        puts("can't compare NULL Task");
        return 0;
    }
    return ((Task*)_taskB)->m_interval < ((Task*)_taskA)->m_interval;
}

int TaskLessThanComparator(const void* _task1, const void* _task2) 
{     
    Task* task1 = (Task*)_task1;     
    Task* task2 = (Task*)_task2;     
    if (!task1 || !task2)     
    {         
        return 0;     
        }     
    if(task1->m_nextExecution.tv_sec < task2->m_nextExecution.tv_sec)     
    {         
        return 1;     
    }
    else if(task1->m_nextExecution.tv_sec > task2->m_nextExecution.tv_sec)     
    {         
        return 0;     
    }     
    else     
    {         
        if(task1->m_nextExecution.tv_nsec < task2->m_nextExecution.tv_nsec)         
        {             
            return 1;         
        }         
        else         
        {             
            return 0;         
        }     
    }
}