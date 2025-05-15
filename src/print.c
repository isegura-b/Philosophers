#include "../inc/philo.h"

void    ft_cleanup(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        pthread_mutex_destroy(&table->philo[i].r_fork);
        pthread_mutex_destroy(&table->philo[i].philo_full);
        i++;
    }
    pthread_mutex_destroy(&table->lock_general.mutex);
    pthread_mutex_destroy(&table->print);
    free(table->philo);
}

void    ft_error(char *error_str, void *set_free)
{
    printf("Error : %s\n", error_str);
    if (set_free)
        free(set_free);
    exit(EXIT_FAILURE);
}

void    print_status(t_philo *philo, int status)
{
    long    current_time;
    int     is_dead;

    current_time = get_time() - philo->table->start_time;
    is_dead = philo->table->dead;
    if (!is_dead)
    {
        pthread_mutex_lock(&philo->table->print);
        if (status == EAT)
            printf(PINK "%6ld %5d is eating\n" RESET, current_time, philo->id);
        else if (status == SLEEP)
            printf(BLUE "%6ld %5d is sleeping\n" RESET, current_time, philo->id);
        else if (status == THINK)
            printf(GREEN "%6ld %5d is thinking\n" RESET, current_time, philo->id);
        else if (status == FORK_R)
            printf(PURPLE_R "%6ld %5d has taken the right fork\n" RESET, current_time, philo->id);
        else if (status == FORK_L)
            printf(PURPLE_L "%6ld %5d has taken the left fork\n" RESET, current_time, philo->id);
        else if (status == DIE)
            printf(RED "%6ld %5d died\n" RESET, current_time, philo->id);
        pthread_mutex_unlock(&philo->table->print);
    }
}

