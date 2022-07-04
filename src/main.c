/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:24:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/05 01:26:02 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long unsigned	get_good_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	displayer(t_philostruct *p, int num_of_phil, char *action)
{
	long unsigned time;

	pthread_mutex_lock(&p->is_talking);
	if (p->can_display == 0)
	{
		time = get_good_time();
		printf("%lu %d %s", time, num_of_phil, action);
	}
	pthread_mutex_unlock(&p->is_talking);
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

void	philo_creator(t_philostruct *p)
{
	int	i;

	i = 1;
	while (i <= p->num_of_phil)
	{
		memset(&p->philo_list[i - 1], 0, sizeof(t_philo));
		p->philo_list[i - 1].philo_num = i;
		p->philo_list[i - 1].num_of_meals = 0;
		p->philo_list[i - 1].last_meal = 0;
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
	usleep(p->time_to_eat * 1000);
	put_fork_down(p, philo_num);
}

void	ft_sleep(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is sleeping\n");
	usleep(p->time_to_sleep * 1000);
}

void	ft_think(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is thinking\n");
}

void	*ft_routine(void *content)
{
	t_philostruct	*p;
	int 			i;

	i = 1;
	p = (t_philostruct *)content;
	pthread_mutex_lock(&p->locker);
	while (p->can_display != 1)
	{
		ft_eat(p, i);
		ft_sleep(p, i);
		ft_think(p, i);
	}
	return (NULL);
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
	pthread_mutex_init(&p->locker, NULL);
}

void	philo_launcher(t_philostruct *p)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&p->locker);
	while (i <= p->num_of_phil)
	{
		pthread_mutex_init(&p->forks[i - 1], NULL);
		pthread_create(&p->philo_list[i - 1].philo, NULL, &ft_routine, p);
		i++;
	}
	pthread_mutex_unlock(&p->locker);
	pthread_create(&p->reaper, NULL, &reaper, p);
	i = 0;
	while (++i <= p->num_of_phil)
		pthread_join(p->philo_list[i - 1].philo, NULL);
	pthread_join(p->reaper, NULL);
}

void	init(t_philostruct *p, char **argv)
{
	p->num_of_phil = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p->num_of_meals = ft_atoi(argv[5]);
	p->philo_list = malloc(p->num_of_phil * sizeof(t_philo) + 1);
	if (!p->philo_list)
		ft_exit(p, "failed to malloc philo");
	p->forks = malloc(p->num_of_phil * sizeof(pthread_mutex_t));
	if (!p->forks)
		ft_exit(p, "failed to malloc forks");	
}

int main(int argc, char **argv)
{
	t_philostruct *p;

	p = malloc(sizeof(t_philostruct));
	if (!p)
		return(0);
	if (argc == 5 || argc == 6)
	{
		
		init(p, argv);
		philo_creator(p);
		pthread_mutex_init(&p->is_talking, NULL);
		philo_launcher(p);
		demallocage(p);
	}
	return (0);
}