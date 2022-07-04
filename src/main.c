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

void	init(t_philostruct *p, char **argv)
{
	int	i;

	i = 0;
	p->num_of_phil = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p->num_of_meals = ft_atoi(argv[5]);
	p->philo_list = malloc(p->num_of_phil * sizeof(t_philo));
	if (!p->philo_list)
		return ;// ft_exit();
	p->forks = malloc(p->num_of_phil * sizeof(pthread_mutex_t));
	if (!p->forks)
		return ;// ft_exit();
	while (i < p->num_of_phil)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		pthread_mutex_init(&p->philo_list[i].philo_locker, NULL);
		i++;
	}
	pthread_mutex_init(&p->locker, NULL);
}

long unsigned	get_good_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	displayer(t_philostruct *p, int num_of_phil, char *action)
{
	long unsigned time;

	if (p->can_display == 0)
	{
		time = get_good_time();
		printf("%lu %d %s", time, num_of_phil, action);
	}
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
		p->philo_list[i - 1].last_meal = 850;
		i++;
	}
}

void	pick_fork(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	if (philo_num == 0)
		left = p->num_of_phil - 1;
	right = philo_num - 1;
	pthread_mutex_lock(&p->forks[left]);
	displayer(p, philo_num, "has taken a fork\n");
	pthread_mutex_lock(&p->forks[right]);
	displayer(p, philo_num, "has taken a fork\n");
}

void	put_fork_down(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	if (philo_num == 1)
		left = p->num_of_phil - 1;
	right = philo_num - 1;
	pthread_mutex_unlock(&p->forks[left]);
	pthread_mutex_unlock(&p->forks[right]);
}

void	ft_eat(t_philostruct *p, int philo_num)
{
	pick_fork(p, philo_num);
	pthread_mutex_lock(&p->philo_list[philo_num].philo_locker);
	p->philo_list[philo_num].last_meal = get_good_time();
	p->philo_list[philo_num].num_of_meals++;
	pthread_mutex_unlock(&p->philo_list[philo_num].philo_locker);
	displayer(p, philo_num, "is eating\n");
	put_fork_down(p, philo_num);
}

void	*ft_routine(void *content)
{
	t_philostruct *p;

	p = (t_philostruct *)content;
	ft_eat(p, 0);
	// ft_sleep(p);
	// ft_think(p);
	return (NULL);
}

void	*reaper(void *content)
{
	t_philostruct *p;
	int i;
	long unsigned time_result;
	int	quit;

	p = (t_philostruct *)content;
	i = 0;
	quit = 0;
	time_result = 0;
	while (quit == 0)
	{
		i = 0;
		while (i <= p->num_of_phil)
		{
			time_result = get_good_time() - p->philo_list[i - 1].last_meal;
			if (time_result >= p->time_to_die)
				quit++;
			i++;
		}
	}
	p->can_display = 1;
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philostruct *p;
	int i;
	int	err;

	err = 0;
	i = 1;
	if (argc == 5 || argc == 6)
	{
		p = malloc(sizeof(t_philostruct));
		init(p, argv);
		philo_creator(p);
		while (i <= p->num_of_phil)
		{
			if (pthread_mutex_init(&p->forks[i - 1], NULL) != 0)
				printf("\n mutex init failed\n");
			err = pthread_create(&p->philo_list[i - 1].philo, NULL, &ft_routine, p);
			if (err != 0)
				printf("\n can't create thread :[%s]", strerror(err));
			i++;
		}
		pthread_mutex_unlock(&p->locker);
		pthread_create(&p->reaper, NULL, &reaper, p);
		i = 0;
		while (++i <= p->num_of_phil)
			pthread_join(p->philo_list[i - 1].philo, NULL);
		pthread_join(p->reaper, NULL);
		// printf("%lu\n", get_good_time());
		// philo_launch(p);
		// while (i < ft_atoi(argv[1]))
		// {
		// 	printf("%d\n", p->philo_list[i].philo_num);
		// 	i++;
		// }
		reaper(p);
		demallocage(p);
	}
}