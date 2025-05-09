#include "../inc/philo.h"

void    ft_cleanup(t_table *table, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        pthread_mutex_destroy(&table->philo[i].r_fork);
        pthread_mutex_destroy(&table->philo[i].philo_full);
        i++;
    }
    pthread_mutex_destroy(&table->lock_general);
    pthread_mutex_destroy(&table->print);
    free(table->philo);
}

static void    ft_init_table(char **av, t_table *table)
{    
    table->nbr_philo = ft_atoi(av[1]);
    table->tt_die = ft_atoi(av[2]);
    table->tt_eat = ft_atoi(av[3]);
    table->tt_sleep = ft_atoi(av[4]);
    if (av[5])
        table->t_eaten = ft_atoi(av[5]);
    else
        table->t_eaten = -1;
    table->dead = 0;
    table->start_time = get_time();
    if (pthread_mutex_init(&table->lock_general, NULL))
        ft_error("mutex error", NULL);
    if (pthread_mutex_init(&table->print, NULL))
        ft_error("mutex error", NULL);
}

static void    ft_init_filo(t_table *table)
{
    int i;

    i = 0;
    table->philo = malloc(sizeof(t_philo) * table->nbr_philo);
    if (!table->philo)
    {
        ft_cleanup(table, 0);
        ft_error("malloc failed", NULL);
    }
    while (i < table->nbr_philo)
    {
        table->philo[i].id = i + 1;
        table->philo[i].table = table;
        table->philo[i].last_eat = 0;
        table->philo[i].nbr_eaten = 0;
        table->philo[i].dead = 0;
        if (pthread_mutex_init(&table->philo[i].r_fork, NULL))
            ft_error("mutex error", NULL);
        if (table->nbr_philo > 1)
            table->philo[i].l_fork = &table->philo[i + 1].r_fork;
        else
            table->philo[i].l_fork = NULL;
        if (pthread_mutex_init(&table->philo[i].philo_full, NULL))
            ft_error("mutex error", NULL);
        i++;
    }
}

static void ft_prep_sim(t_table *table)
{
    int i;

    i = 0;
    pthread_mutex_lock(&table->lock_general);
    while (i < table->nbr_philo)
    {
        if (pthread_create(&table->philo[i].thread, NULL, ft_routine, &table->philo[i]))
        {
            pthread_mutex_unlock(&table->lock_general);
            ft_error("thread creation failed", NULL);
        }
        i++;
    }
    pthread_mutex_unlock(&table->lock_general);
    i = 0;
    while (i < table->nbr_philo)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
}


int ft_init(int ac, char **av, t_table *table)
{
    ft_init_table(av, table);
    ft_init_filo(table);
    ft_prep_sim(table);
    ft_cleanup(table, table->nbr_philo);
    return (0);
}