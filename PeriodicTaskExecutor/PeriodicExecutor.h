#ifndef __PERIOSDICEXECUTOR_H__
#define __PERIOSDICEXECUTOR_H__
#include <sys/types.h>

typedef struct PeriodicExecutor PeriodicExecutor;

PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clk_id);
void PeriodicExecutorDestroy(PeriodicExecutor* _executor);
int PeriodicExecutorAdd(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _period_ms);
size_t PeriodicExecutorRun(PeriodicExecutor* _executor);
size_t PeriodicExecutorPause(PeriodicExecutor* _executor);

#endif /* __PERIOSDICEXECUTOR_H__ */