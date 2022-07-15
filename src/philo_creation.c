/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 03:43:46 by qvy               #+#    #+#             */
/*   Updated: 2022/07/15 03:44:41 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_luncher_helper(t_philostruct *p)
{
	while (s()->which_philo < p->num_of_phil)
	{
		usleep(50);
		pthread_mutex_lock(&p->locker);
		pthread_create(&p->philo_list[s()->which_philo].philo,
			NULL, &ft_routine, p);
		s()->which_philo = s()->which_philo + 1;
		pthread_mutex_unlock(&p->locker);
	}
}

void	philo_launcher(t_philostruct *p)
{
	int	i;

	i = -1;
	s()->which_philo = 0;
	if (p->num_of_phil == 1)
	{
		micro_sleep(p->time_to_die * 1000);
		printf("\033[0;32m%lu 1 has died\033[0m\n", get_good_time() - p->start);
	}
	else
	{
		philo_luncher_helper(p);
		micro_sleep(10000);
		pthread_create(&p->reaper, NULL, &reaper, p);
		if (p->num_of_meals > -1)
			pthread_create(&p->grailleur, NULL, &grailleur, p);
		while (++i < p->num_of_phil)
			pthread_join(p->philo_list[i].philo, NULL);
		pthread_join(p->reaper, NULL);
		if (p->num_of_meals > -1)
			pthread_join(p->grailleur, NULL);
	}
}

void	philo_creator(t_philostruct *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_phil)
	{
		memset(&p->philo_list[i], 0, sizeof(t_philo));
		p->philo_list[i].philo_num = i;
		p->philo_list[i].num_of_meals = 0;
		p->philo_list[i].last_meal = 0;
		pthread_mutex_init(&p->philo_list[i].philo_locker, NULL);
		i++;
	}
}
