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

void	demallocage(t_philostruct *p)
{
	free(p->philo_list);
	free(p);
}

void	philo_creator(t_philostruct *p)
{
	int	i;

	i = 1;
	p->philo_list = malloc(sizeof(t_philo) * p->num_of_phil + 1);
	while (i <= p->num_of_phil)
	{
		p->philo_list[i - 1].philo_num = i;
		p->philo_list[i - 1].num_of_meals = 0;
		p->philo_list[i - 1].last_meal = 0;
		i++;
	}
}

void	init(t_philostruct *p, char **argv)
{
	p->num_of_phil = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->num_of_meals = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_philostruct *p;
	int i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		p = malloc(sizeof(t_philostruct));
		init(p, argv);
		philo_creator(p);
		while (i < ft_atoi(argv[1]))
		{
			printf("%d\n", p->philo_list[i].philo_num);
			i++;
		}
	}
	demallocage(p);
}