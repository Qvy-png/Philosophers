/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:24:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/05/26 14:14:53 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

https://github.com/Glagan/42-Philosophers/tree/master/philo_one

void	demallocage(struct s_philostruct *p)
{
	free(p);
}

void	init(struct s_philostruct *p)
{
	p->argc = 0;
	p->num_of_phil = 0;
	p->time_to_die = 0;
	p->time_to_eat = 0;
	p->time_to_die = 0;
	p->num_of_eat = 0;
	p->argv = NULL;
}

void	filler(struct s_philostruct *p, int argc, char **argv)
{
	p->argv = argv;
	p->num_of_phil = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		p->num_of_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	struct s_philostruct	*p;

	p = malloc(sizeof(struct s_philostruct));
	if (!p)
		return (0);
	init(p);
	if (argc >= 5 && argc <= 6)
	{
		filler(p, argc, argv);
	}
	demallocage(p);
	return (0);
}
