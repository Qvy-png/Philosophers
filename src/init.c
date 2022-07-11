/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:33:00 by qvy               #+#    #+#             */
/*   Updated: 2022/07/11 18:49:25 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_singleton	*s(void)
{
	static t_singleton	*s = NULL;

	if (!s)
	{
		s = malloc(sizeof(t_singleton));
		if (!s)
			return (NULL);
	}
	return (s);
}

void	init(t_philostruct *p, char **argv)
{
	t_singleton	*single;

	single = s();
	p->num_of_phil = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->can_display = 0;
	s()->which_philo = 0;
	if (argv[5])
		p->num_of_meals = ft_atoi(argv[5]);
	p->philo_list = malloc(p->num_of_phil * sizeof(t_philo));
	if (!p->philo_list)
		ft_exit(p, "failed to malloc philo\n");
	p->forks = malloc(sizeof(pthread_mutex_t) * (p->num_of_phil));
	if (!p->forks)
		ft_exit(p, "failed to malloc forks\n");
	p->start = get_good_time();
	init_mutex(p);
}

void	init_mutex(t_philostruct *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_phil)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		pthread_mutex_init(&p->philo_list[i].philo_locker, NULL);
		i++;
	}
	pthread_mutex_init(&p->is_talking, NULL);
	pthread_mutex_init(&p->locker, NULL);
	pthread_mutex_init(&p->is_talking, NULL);
}
