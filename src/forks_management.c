/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 03:48:44 by qvy               #+#    #+#             */
/*   Updated: 2022/07/15 03:50:59 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	pick_fork(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	right = philo_num - 1;
	if (philo_num == 1)
		left = p->num_of_phil - 1;
	else
		left = right - 1;
	if (philo_num % 2 == 0)
	{
		pthread_mutex_lock(&p->forks[left]);
		displayer(p, philo_num, "has taken a fork\n");
		pthread_mutex_lock(&p->forks[right]);
		displayer(p, philo_num, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&p->forks[right]);
		displayer(p, philo_num, "has taken a fork\n");
		pthread_mutex_lock(&p->forks[left]);
		displayer(p, philo_num, "has taken a fork\n");
	}
}

void	put_fork_down(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	right = philo_num - 1;
	if (philo_num == 1)
		left = p->num_of_phil - 1;
	else
		left = right - 1;
	if (philo_num % 2 == 0)
	{
		pthread_mutex_unlock(&p->forks[right]);
		pthread_mutex_unlock(&p->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&p->forks[left]);
		pthread_mutex_unlock(&p->forks[right]);
	}
}
