#include "PeriodicExecutor.h"
#include <time.h>
#include <stdio.h>

static int Task1(void* _context);
static int Task2(void* _context);
static int Task3(void* _context);
static int Task4(void* _context);
static int PauseTask(void* _context);

int main(void)
{
    clockid_t clk_id = CLOCK_MONOTONIC/*CLOCK_REALTIME_COARSE CLOCK_REALTIME CLOCK_MONOTONIC*/;
    PeriodicExecutor* executor = PeriodicExecutorCreate("Executor", clk_id);

    PeriodicExecutorAdd(executor, Task1, (void*)"Task1", 4);
    PeriodicExecutorAdd(executor, Task2, (void*)"Task2", 10);
    PeriodicExecutorAdd(executor, Task3, (void*)"Task3", 3);
    PeriodicExecutorAdd(executor, Task4, (void*)"Task4", 6);
    PeriodicExecutorAdd(executor, PauseTask, (void*)executor, 20);
    PeriodicExecutorPause(executor);
    PeriodicExecutorRun(executor);
    PeriodicExecutorDestroy(executor);
    PeriodicExecutorDestroy(executor);
    return 0;
}

int Task1(void* _context)
{
    puts("Running Task 1");
    return 0;
}

int Task2(void* _context)
{
    puts("Running Task 2");
    return 0;
}

int Task3(void* _context)
{
    puts("Running Task 3");
    return 0;
}

int Task4(void* _context)
{
    puts("Running Task 4");
    return 0;
}

int PauseTask(void* _context)
{
    PeriodicExecutorPause((PeriodicExecutor*)_context);
    return 1;
}