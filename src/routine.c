/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 03:45:22 by qvy               #+#    #+#             */
/*   Updated: 2022/07/15 03:45:59 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_eat(t_philostruct *p, int philo_num)
{
	pick_fork(p, philo_num);
	pthread_mutex_lock(&p->philo_list[philo_num - 1].philo_locker);
	p->philo_list[philo_num - 1].last_meal = get_good_time();
	p->philo_list[philo_num - 1].num_of_meals += 1;
	pthread_mutex_unlock(&p->philo_list[philo_num - 1].philo_locker);
	displayer(p, philo_num, "is eating\n");
	micro_sleep(p->time_to_eat * 1000);
	put_fork_down(p, philo_num);
}

void	ft_sleep(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is sleeping\n");
	micro_sleep(p->time_to_sleep * 1000);
}

void	ft_think(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is thinking\n");
	if (p->time_to_eat >= p->time_to_sleep)
		micro_sleep((p->time_to_eat - p->time_to_sleep + 1) * 1000);
}

void	*ft_routine(void *content)
{
	t_philostruct	*p;
	int				i;
	int				bricolage;

	p = (t_philostruct *)content;
	pthread_mutex_lock(&p->locker);
	i = s()->which_philo;
	bricolage = p->can_display;
	pthread_mutex_unlock(&p->locker);
	while (bricolage != 1)
	{
		pthread_mutex_lock(&p->locker);
		bricolage = p->can_display;
		pthread_mutex_unlock(&p->locker);
		ft_eat(p, i);
		ft_sleep(p, i);
		ft_think(p, i);
	}
	return (NULL);
}
