/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:24:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/08 00:54:17 by qvy              ###   ########.fr       */
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
		time = get_good_time()- p->start;
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
		i = 1;
		while (i <= p->num_of_phil &&  p->philo_list[i - 1].last_meal > 0)
		{
			pthread_mutex_lock(&p->philo_list[i - 1].philo_locker);
			time_result = get_good_time() - p->philo_list[i - 1].last_meal;
			pthread_mutex_unlock(&p->philo_list[i - 1].philo_locker);
			printf("scan me : %lu\n", time_result);
			if (time_result >= p->time_to_die)
				quit++;
			i++;
		}
	}
	p->can_display = 1;
	printf("\033[0;32mhahaha je suis la mort\033[0m\n%lu", p->start);
	return (NULL);
}

void	philo_creator(t_philostruct *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_phil)
	{
		memset(&p->philo_list[i ], 0, sizeof(t_philo));
		p->philo_list[i].philo_num = i;
		p->philo_list[i].num_of_meals = 0;
		p->philo_list[i].last_meal = 0;
		i++;
	}
}

void	pick_fork(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	if (philo_num == 1)
		left = p->num_of_phil - 2;
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

	printf("\033[0;31mphilo%d : puts fork down\033[0m\n", philo_num);
	if (philo_num == 1)
		left = p->num_of_phil - 2;
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

	p = (t_philostruct *)content;
	i = p->which_philo + 1;
	while (p->can_display != 1) // mettre aussi un compteur dans la struct du philo pour compter le nombre de repas, et faire une fonction qui va check si tous les philos ont fini de manger
	{
		ft_eat(p, i);
		ft_sleep(p, i);
		ft_think(p, i);
	}
	return (NULL);
}

void	philo_launcher(t_philostruct *p)
{
	int	i;
	
	i = 0;
	pthread_mutex_init(&p->locker, NULL);
	pthread_mutex_lock(&p->locker);
	while (p->which_philo <= p->num_of_phil)
	{
		pthread_mutex_init(&p->forks[p->which_philo], NULL);
		pthread_create(&p->philo_list[p->which_philo].philo, NULL, &ft_routine, p);
		p->which_philo++;
	}
	pthread_mutex_unlock(&p->locker);
	pthread_create(&p->reaper, NULL, &reaper, p);
	while (++i <= p->num_of_phil)
		pthread_join(p->philo_list[i].philo, NULL);
	pthread_join(p->reaper, NULL);
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