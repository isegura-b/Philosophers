#include "../inc/philo.h"

int ft_eat(t_philo *philo)
{
    if (philo->table->dead == 1)
        return (1);
    if (philo->table->t_eaten == -1 && philo->nbr_eaten == philo->table->t_eaten)
        return (1);
    if (philo->table->nbr_philo > 1)
        eat(philo);
    else //solo un filosofo no puede comer
    
    return (0);
}

void *ft_routine(void *arg)
{
    t_philo *philo;
    
    philo = arg; //recibe el puntero(void) a la estructura t_philo
    pthread_mutex_lock(&philo->table->lock_start); //intentan block, no puede, y se esperan a que el ft_prep_sim desbloquee.
    pthread_mutex_unlock(&philo->table->lock_start);

    if (philo->id % 2 == 0) //esperan los pares aque lo impares coman
        ft_usleep(philo->table->tt_eat);
    while (is_alive(philo))
    {
        if (ft_eat(philo))
            return ;
        ft_sleep(philo);
        ft_think(philo);
    }
    return ;
}
