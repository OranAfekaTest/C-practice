#ifndef __CALCTIME_H__
#define __CALCTIME_H__
#include <stddef.h>
#include <sys/types.h>

void WaitTaskPeriod(size_t _period);
size_t GetUpdatedInterval(size_t _interval, clockid_t _clk_id);

#endif /* __CALCTIME_H__ */