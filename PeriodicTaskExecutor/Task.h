#ifndef __TASK_H__
#define __TASK_H__
#include <stddef.h> /*size_t*/
#include <sys/types.h>/*clockid_t*/

typedef struct Task Task;
typedef int (*fpTask)(void* _context);

Task* TaskCreate(fpTask _taskFunc, size_t _interval, void* _context, int _isPause);
void TaskDestroy(void* _task);
int TaskRun(Task* Task);
int TaskComperator(const void* _taskA, const void* _taskB);
void TaskUpdateInterval(Task* _task, clockid_t _clk_id);


#endif /* __TASK_H__ */
