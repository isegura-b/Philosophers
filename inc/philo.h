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
	FORK_R,
	FORK_L,

};


#define BLUE  "\033[1;38;5;45m" //sleep - Bright cyan
#define GREEN  "\033[1;38;5;46m" //think - Bright green
#define RED  "\033[1;38;5;196m" //die - Bright red
#define PINK  "\033[1;38;5;213m" //eat - Bright magenta
#define PURPLE_R  "\033[1;38;5;183m" //fork_r - Soft magenta
#define PURPLE_L  "\033[1;38;5;147m" //fork_l - Soft purple
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


//init.c
int     ft_init(char **av, t_table *table);

//mutex.c
void    lock_mutex(t_mutex_status *status);
void    unlock_mutex(t_mutex_status *status);

//parsing.c
int     ft_atoi(char *nptr);
int     arg_is_digit(int ac, char **av);
int     ft_int_lim(int ac, char **av);
int     ft_parsing(int ac, char **av);

//routine.c
int     ft_eat(t_philo *philo);
int    ft_sleep(t_philo *philo);
int    ft_think(t_philo *philo);
void    *ft_routine(void *arg);

//print.c
void    ft_cleanup(t_table *table);
void    ft_error(char *error_str, void *set_free);
void    print_status(t_philo *philo, int status);

//utils.c
void    ft_usleep(long time);
long get_elapsed_time(void);
long    get_time(void);
int     someone_dead(t_philo *philo);
int     is_not_alive(t_philo *philo);

#endif
