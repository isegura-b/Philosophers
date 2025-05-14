#include "../inc/philo.h"

void lock_mutex(t_mutex_status *status)
{
    pthread_mutex_lock(&status->mutex);
    status->is_locked = 1;
}

void unlock_mutex(t_mutex_status *status)
{
    status->is_locked = 0;
    pthread_mutex_unlock(&status->mutex);
}

