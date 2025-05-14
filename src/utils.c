#include "../inc/philo.h"

long    get_time(void)
{
    struct timeval  time;
	static time_t	start_time;

	if (start_time == 0)
	{
		gettimeofday(&time, NULL);
		start_time = ((time.tv_sec * 1000) + time.tv_usec / 1000);
	}
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001) - start_time);
}

void    ft_usleep(long time)
{
    long    start;

    start = get_time();
    while (get_time() - start < time)
        usleep(100);
}

int someone_dead(t_philo *philo)
{
    if (philo->table->lock_general.is_locked || philo->table->dead)
        return (1);
    return (0);
}

int is_alive(t_philo *philo)
{
    long current_time;

    current_time = get_time();
    if (current_time - philo->last_eat >= philo->table->tt_die)
    {
        lock_mutex(&philo->table->lock_general);
        if (!philo->table->dead)
        {
            philo->table->dead = 1;
            print_status(philo, DIE);
        }
        return (0);
    }
    return (1);
}
