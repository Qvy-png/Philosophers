/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:33:00 by qvy               #+#    #+#             */
/*   Updated: 2022/07/07 18:09:36 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init(t_philostruct *p, char **argv)
{
	p->num_of_phil = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
    p->can_display = 0;
    p->which_philo = 0;
	if (argv[5])
		p->num_of_meals = ft_atoi(argv[5]);
	p->philo_list = malloc(p->num_of_phil * sizeof(t_philo) + 1);
	if (!p->philo_list)
		ft_exit(p, "failed to malloc philo");
	p->forks = malloc(p->num_of_phil * sizeof(pthread_mutex_t));
	if (!p->forks)
		ft_exit(p, "failed to malloc forks");
	p->start = get_good_time();	
}

void	init_mutex(t_philostruct *p)
{
	int	i;

	i = 1;
	while (i <= p->num_of_phil)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		pthread_mutex_init(&p->philo_list[i].philo_locker, NULL);
		i++;
	}
	pthread_mutex_init(&p->is_talking, NULL);
    // pthread_mutex_init(&p->locker, NULL);
}