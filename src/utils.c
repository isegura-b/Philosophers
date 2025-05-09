#include "../inc/philo.h"

long    get_time(void)
{
    struct timeval  time;
	static time_t	start_time;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	}
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001) - start_time);
}

void    ft_usleep(long time)
{
    long    start;

    start = get_time();
    while (get_time() - start < time)
        usleep(100);
}

int is_alive(t_philo *philo)
{
    long current_time;

    current_time = get_time();
    pthread_mutex_lock(&philo->table->lock_general);
    if (current_time - philo->last_eat >= philo->table->tt_die)
    {
        print_status(philo, current_time, DIE);
        philo->table->dead = 1;
        pthread_mutex_unlock(&philo->table->lock_general);
        return (0);
    }
    pthread_mutex_unlock(&philo->table->lock_general);
    return (1);
}
