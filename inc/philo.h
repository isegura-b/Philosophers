#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

enum
{
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK,
};


#define BLUE  "\033[34m" //sleep
#define GREEN  "\033[32m" //think
#define RED  "\033[31m" //die
#define PINK  "\033[35m" //eat
#define PURPLE  "\033[95m" //fork
#define RESET "\033[0m"

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_mutex_status
{
    int             is_locked;
    pthread_mutex_t mutex;
} t_mutex_status;

struct s_philo
{
    int                 id;
    int                 last_eat; //para ver si se muere
    int                 nbr_eaten;
    int                 dead; //0=no 1=yes
    pthread_mutex_t     r_fork;
    pthread_mutex_t     *l_fork;
    pthread_mutex_t     philo_full;
    pthread_t           thread;
    t_table             *table;
};

struct s_table
{
    int             nbr_philo;
    int             tt_die;
    int             tt_eat;
    int             tt_sleep;
    int             t_eaten;
    int             dead; // 0-no 1-yes
    long            start_time;
    t_mutex_status  lock_general;
    pthread_mutex_t print; 
    t_philo        *philo;
};


int     ft_parsing(int ac, char **av);
void    ft_error(char *error_str, void *set_free);
int     ft_int_lim(int ac, char **av);
int     arg_is_digit(int ac, char **av);
int     ft_atoi(char *nptr);
int     is_alive(t_philo *philo);
void    ft_usleep(long time);
long    get_time(void);
void    ft_sleep(t_philo *philo);
void    ft_think(t_philo *philo);
int     ft_eat(t_philo *philo);
void    *ft_routine(void *arg);
int     ft_init(char **av, t_table *table);
void    eat(t_philo *philo);
int     someone_dead(t_philo *philo);
void    print_status(t_philo *philo, int status);
void    ft_cleanup(t_table *table);

// Mutex status functions
void    lock_mutex(t_mutex_status *status);
void    unlock_mutex(t_mutex_status *status);

#endif