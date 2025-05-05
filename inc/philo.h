#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

int     ft_parsing(int ac, char **av);
void    ft_error(char *error_str, void set_free)
int     ft_int_lim(int ac, char **av);
int     arg_is_digit(int ac, char **av);
int	    ft_atoi(char *nptr);

typedef struct t_philo
{

}   t_philo;

typedef struct s_table
{
    int     nbr_filo;
    int		tt_die;
	int		tt_eat;
	int		tt_sleep;
    int     t_eaten;
    int     dead; // 0-false 1-true
    t_philo *philo;
}   t_table;

#endif