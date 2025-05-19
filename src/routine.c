/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:57:35 by isegura-          #+#    #+#             */
/*   Updated: 2025/05/16 11:03:10 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		print_status(philo, FORK_R);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK_L);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK_L);
		pthread_mutex_lock(&philo->r_fork);
		print_status(philo, FORK_R);
	}
	philo->last_eat = get_time() - philo->table->start_time;
	philo->nbr_eaten++;
	print_status(philo, EAT);
	ft_usleep(philo->table->tt_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	ft_eat(t_philo *philo)
{
	if (someone_dead(philo) || is_not_alive(philo))
		return (1);
	if (philo->table->nbr_philo > 1)
		eat(philo);
	else
	{
		pthread_mutex_lock(&philo->r_fork);
		print_status(philo, FORK_R);
		ft_usleep(philo->table->tt_die);
		pthread_mutex_unlock(&philo->r_fork);
		someone_dead(philo);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (someone_dead(philo) || is_not_alive(philo))
		return (1);
	print_status(philo, SLEEP);
	ft_usleep(philo->table->tt_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (someone_dead(philo) || is_not_alive(philo))
		return (1);
	print_status(philo, THINK);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	lock_mutex(&philo->table->lock_general);
	unlock_mutex(&philo->table->lock_general);
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->tt_eat);
	while (!someone_dead(philo))
	{
		if (ft_eat(philo))
			return (NULL);
		if (philo->table->t_eaten != -1
			&& philo->nbr_eaten >= philo->table->t_eaten)
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
	}
	return (NULL);
}
