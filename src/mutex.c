/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:57:05 by isegura-          #+#    #+#             */
/*   Updated: 2025/05/16 10:57:06 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_mutex(t_mutex_status *status)
{
	pthread_mutex_lock(&status->mutex);
	status->is_locked = 1;
}

void	unlock_mutex(t_mutex_status *status)
{
	status->is_locked = 0;
	pthread_mutex_unlock(&status->mutex);
}
