/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:57:25 by isegura-          #+#    #+#             */
/*   Updated: 2025/05/16 10:57:27 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *nptr)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (*nptr == ' ' || (8 < *nptr && *nptr < 14))
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		i++;
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (i >= 2)
			return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 +(*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

int arg_is_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '\0') 
			return (1);
		while (av[i][j])
		{
			if(av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int ft_int_lim(int ac, char **av)
{
	int	i;
	long	num;

	i = 1;
	while(i < ac)
	{
		num = ft_atoi(av[i]);
		if(num <= 0 || num > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

int ft_parsing(int ac, char **av)
{
	if (ft_int_lim(ac, av) || arg_is_digit(ac, av))
		return (ft_error("invalid args", NULL), 1);
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0)
		return (ft_error("invalid number of filos", NULL), 1);
	return (0);
}
