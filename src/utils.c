/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:57:21 by qvy               #+#    #+#             */
/*   Updated: 2022/07/13 22:01:38 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}

void	ft_exit(t_philostruct *p, char *message)
{
	// int	i;

	// i = 0;
	if (message)
		printf("Error, %s failed\n", message);
	demallocage(p);
	exit(1);
}

void	demallocage(t_philostruct *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_phil)
	{
		pthread_mutex_destroy(&p->philo_list[i].philo_locker);
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&p->locker);
	pthread_mutex_destroy(&p->is_talking);
	free(p->forks);
	free(s());
	free(p->philo_list);
}
