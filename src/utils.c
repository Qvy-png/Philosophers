/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:57:21 by qvy               #+#    #+#             */
/*   Updated: 2022/07/16 18:07:04 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	ft_atoi(const char *str)
{
	long	i;
	int		sign;
	long	number;

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

void	micro_sleep(long unsigned time)
{
	long unsigned	actual;

	actual = get_good_time();
	while ((get_good_time() - actual) * 1000 < time)
		usleep(50);
}

long unsigned	get_good_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	displayer(t_philostruct *p, int num_of_phil, char *action)
{
	long unsigned	time;

	pthread_mutex_lock(&p->locker);
	time = get_good_time() - p->start;
	pthread_mutex_lock(&p->is_talking);
	if (p->can_display == 0)
		printf("%lu %d %s", time, num_of_phil, action);
	pthread_mutex_unlock(&p->is_talking);
	pthread_mutex_unlock(&p->locker);
}
