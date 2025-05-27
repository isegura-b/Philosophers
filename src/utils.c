/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:01:45 by isegura-          #+#    #+#             */
/*   Updated: 2025/05/27 09:52:49 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(void)
{
	struct timeval	time;
	static time_t	start_time;

	if (start_time == 0)
	{
		gettimeofday(&time, NULL);
		start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	}
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}

void	ft_usleep(long time)
{
	long	start;
	long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= time)
			break ;
		usleep(100);
	}
}

int	someone_dead(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->table->lock_general.mutex);
	ret = philo->table->dead;
	pthread_mutex_unlock(&philo->table->lock_general.mutex);
	return (ret);
}

int	is_not_alive(t_philo *philo)
{
	long	current_time;
	int		is_dead;

	current_time = get_time();
	pthread_mutex_lock(&philo->table->lock_general.mutex);
	if (current_time - philo->last_eat >= philo->table->tt_die
		&& !philo->table->dead)
	{
		philo->table->dead = 1;
		is_dead = 1;
		pthread_mutex_unlock(&philo->table->lock_general.mutex);
		print_status(philo, DIE);
		return (1);
	}
	is_dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->lock_general.mutex);
	return (is_dead);
}
