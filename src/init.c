/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:56:39 by isegura-          #+#    #+#             */
/*   Updated: 2025/05/19 13:39:31 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_init_table(char **av, t_table *table)
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
	table->lock_general.is_locked = 0;
	if (pthread_mutex_init(&table->lock_general.mutex, NULL))
		ft_error("mutex error", (void *)table);
	if (pthread_mutex_init(&table->print, NULL))
		ft_error("mutex error", (void *)table);
}

static void	ft_init_philo_2(t_table *table, int i)
{
	table->philo[i].id = i + 1;
	table->philo[i].table = table;
	table->philo[i].last_eat = 0;
	table->philo[i].nbr_eaten = 0;
	table->philo[i].dead = 0;
}

static void	ft_init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->nbr_philo);
	if (!table->philo)
	{
		ft_cleanup(table);
		ft_error("malloc failed", (void *)table);
	}
	while (i < table->nbr_philo)
	{
		ft_init_philo_2(table, i);
		if (pthread_mutex_init(&table->philo[i].r_fork, NULL))
			ft_error("mutex error", (void *)table);
		if (table->nbr_philo > 1)
			table->philo[i].l_fork = &table->philo[(i + 1)
				% table->nbr_philo].r_fork;
		else
			table->philo[i].l_fork = NULL;
		if (pthread_mutex_init(&table->philo[i].philo_full, NULL))
			ft_error("mutex error", (void *)table);
		i++;
	}
}

static void	ft_prep_sim(t_table *table)
{
	int	i;

	i = 0;
	lock_mutex(&table->lock_general);
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				ft_routine, &table->philo[i]))
		{
			unlock_mutex(&table->lock_general);
			ft_error("thread creation failed", (void *)table);
		}
		i++;
	}
	unlock_mutex(&table->lock_general);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))
		{
			ft_error("thread join failed", (void *)table);
		}
		i++;
	}
}

int	ft_init(char **av, t_table *table)
{
	ft_init_table(av, table);
	ft_init_philo(table);
	ft_prep_sim(table);
	ft_cleanup(table);
	return (0);
}
