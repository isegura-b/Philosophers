#include "../inc/philo.h"

static void    ft_init_table(char **av, t_table table)
{    
    table->nbr_filo = ft_atoi(av[1]);
    table->tt_die = ft_atoi(av[2]);
    table->tt_eat = ft_atoi(av[3]);
    table->tt_sleep = ft_atoi(av[4]);
    if (av[5])
        table->t_eaten = ft_atoi(av[5]);
    else
        table->t_eaten = -1;
    table->dead = 0;
}

int ft_init(int ac, char **av, t_table table)
{
    ft_init_table(av, table);
    ft_init_filo(av, table);
}