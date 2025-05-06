#include "../inc/philo.h"

long    get_time(void)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    ft_usleep(long time)
{
    long    start;

    start = get_time();
    while (get_time() - start < time)
        usleep(100);
} 