#include "CalcTime.h"
#include <unistd.h> /*usleep*/
#include <time.h>
/*#include <stddef.h>
#include <sys/types.h>*/
#define MILLION 1000000
#define THOUSEND 1000

static struct timespec ts;

void WaitTaskPeriod(size_t _period)
{
    usleep(_period * THOUSEND);
}

size_t GetUpdatedInterval(size_t _interval, clockid_t _clk_id)
{
    /*timespec_get(&ts, TIME_UTC);*/
    clock_gettime(_clk_id ,&ts);
    return (ts.tv_nsec / MILLION) + (ts.tv_sec * THOUSEND) + _interval;
}
