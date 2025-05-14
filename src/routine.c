#include "../inc/philo.h"

int ft_eat(t_philo *philo)
{
    if (philo->table->dead == 1)
        return (1);
    if (philo->table->nbr_philo > 1)
        eat(philo);
    else //solo un filosofo no puede comer
        
    return (0);
}

void *ft_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg; //recibe el puntero(void) a la estructura t_philo
    lock_mutex(&philo->table->lock_general); //intentan block, no puede, y se esperan a que el ft_prep_sim desbloquee.
    unlock_mutex(&philo->table->lock_general);

    if (philo->id % 2 == 0) //esperan los pares aque lo impares coman
        ft_usleep(philo->table->tt_eat);
    while (is_alive(philo))
    {
        if (someone_dead(philo) || ft_eat(philo))
            break;
        if (philo->table->t_eaten != -1 && philo->nbr_eaten >= philo->table->t_eaten) //?¿
            break;
        if (someone_dead(philo) || ft_sleep(philo))
            break;
        if (someone_dead(philo) || ft_think(philo))
            break;
    }
    if (philo->table->lock_general.is_locked == 1)
        unlock_mutex(&philo->table->lock_general);
    return (NULL);
}
