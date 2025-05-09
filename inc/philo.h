#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

int     ft_parsing(int ac, char **av);
void    ft_error(char *error_str, void set_free);
int     ft_int_lim(int ac, char **av);
int     arg_is_digit(int ac, char **av);
int	    ft_atoi(char *nptr);
int     is_alive(t_philo *philo);
void    ft_usleep(long time);
long    get_time(void);
void    ft_sleep(t_philo *philo);
void    ft_think(t_philo *philo);
void    ft_eat(t_philo *philo);

enum
{
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK,
};

typedef struct t_philo
{
    int                 id;
    int                 last_eat; //para ver si se muere
    int                 nbr_eaten;
    int                 dead; //0=no 1=yes
    pthread_mutex_t     r_fork;
    pthread_mutex_t     *l_fork;
    pthread_mutex_t     dead_mutex;
    pthread_mutex_t     print;
    pthread_t           thread;
    t_table             *table;
}   t_philo;

typedef struct s_table
{
    int     nbr_philo;
    int		tt_die;
	int		tt_eat;
	int		tt_sleep;
    int     t_eaten;
    int     dead; // 0-no 1-yes
    int     time_start;
    pthread_mutex_t lock_general;
    pthread_mutex_t print;
    t_philo *philo;
}   t_table;

#endif