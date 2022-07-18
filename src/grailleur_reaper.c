/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grailleur_reaper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 03:40:19 by qvy               #+#    #+#             */
/*   Updated: 2022/07/18 02:30:31 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	grailleur_helper(t_philostruct *p, int quit, int count, int i)
{
	while (quit == 0)
	{
		i = 0;
		count = 0;
		while (i < p->num_of_phil)
		{
			pthread_mutex_lock(&p->philo_list[i].philo_locker);
			if (p->philo_list[i].num_of_meals == p->num_of_meals)
				count++;
			if (count == p->num_of_phil)
				quit++;
			pthread_mutex_unlock(&p->philo_list[i].philo_locker);
			pthread_mutex_lock(&p->locker);
			if (p->can_display == 1)
				quit++;
			pthread_mutex_unlock(&p->locker);
			i++;
		}
	}
}

void	*grailleur(void *content)
{
	t_philostruct	*p;
	int				i;
	int				quit;
	int				count;

	p = (t_philostruct *)content;
	i = 0;
	quit = 0;
	count = 0;
	grailleur_helper(p, quit, count, i);
	pthread_mutex_lock(&p->locker);
	if (p->can_display == 0)
		p->can_display = 1;
	pthread_mutex_unlock(&p->locker);
	return (NULL);
}

int	reaper_helper(t_philostruct *p, long unsigned time_result, int i)
{
	if (time_result >= p->time_to_die)
	{
		pthread_mutex_lock(&p->locker);
		if (p->can_display == 0)
		{	
			p->can_display = 1;
			printf("\033[0;32m%lu %d has died\033[0m\n",
				get_good_time() - p->start, i + 1);
		}
		return (pthread_mutex_unlock(&p->locker), 1);
	}
	return (0);
}

void	*reaper(void *content)
{
	t_philostruct	*p;
	int				i;
	long unsigned	time_result;
	int				meal;

	p = (t_philostruct *)content;
	i = 0;
	time_result = 0;
	meal = 0;
	while (1)
	{
		i = -1;
		while (++i < p->num_of_phil)
		{
			pthread_mutex_lock(&p->philo_list[i].philo_locker);
			meal = p->philo_list[i].last_meal;
			if (meal > 0)
				time_result = get_good_time() - p->philo_list[i].last_meal;
			pthread_mutex_unlock(&p->philo_list[i].philo_locker);
			if (reaper_helper(p, time_result, i) == 1)
				return (NULL);
		}
	}
}
