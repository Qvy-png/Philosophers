/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:24:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/10 21:39:08 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	micro_usleep(int time)
{
	int		i;

	i = 0;
	while (i < time)
	{
		usleep(1000);
		i++;
	}
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
		// printf("i was here\n");
		i = 0;
		while (i < p->num_of_phil /*&&  p->philo_list[i].last_meal > 0*/)
		{
			if (p->philo_list[i].last_meal <= 0)
				i++;
			pthread_mutex_lock(&p->philo_list[i].philo_locker);
			time_result = get_good_time() - p->philo_list[i].last_meal;
			// printf("%lu - %lu = %lu\n", get_good_time(), p->philo_list[i].last_meal, get_good_time() - p->philo_list[i].last_meal);
			pthread_mutex_unlock(&p->philo_list[i].philo_locker);
			// printf("\033[0;32mscan me : %lu - %lu\033[0m\n", time_result, p->time_to_die);
			if (time_result >= p->time_to_die)
				quit++;
			i++;
		}
	}
	p->can_display = 1;
	printf("\033[0;32mhahaha je suis la mort\033[0m\n");
	return (NULL);
}

void	philo_creator(t_philostruct *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_phil)
	{
		// printf("%d\n", i);
		memset(&p->philo_list[i], 0, sizeof(t_philo));
		p->philo_list[i].philo_num = i;
		p->philo_list[i].num_of_meals = 0;
		p->philo_list[i].last_meal = 0;
		pthread_mutex_init(&p->philo_list[i].philo_locker, NULL);
		// p->philo_list[i].can_sleep = 0;
		// p->philo_list[i].can_think = 0;
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void	pick_fork(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	
	right = philo_num - 1;
	if (philo_num == 1)
		left = p->num_of_phil - 1;
	else
		left = right - 1;
	// printf("Je suis philo %d, gauche = %d et droite = %d\n", philo_num, left, right);
	
	if (!((philo_num % 2) == 0))
	{
		pthread_mutex_lock(&p->forks[left]);
		displayer(p, philo_num, "has taken a fork\n");
		pthread_mutex_lock(&p->forks[right]);
		displayer(p, philo_num, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&p->forks[right]);
		displayer(p, philo_num, "has taken a fork\n");
		pthread_mutex_lock(&p->forks[left]);
		displayer(p, philo_num, "has taken a fork\n");
	}
}

void	put_fork_down(t_philostruct *p, int philo_num)
{
	int	left;
	int	right;

	
	right = philo_num - 1;
	if (philo_num == 1)
		left = p->num_of_phil - 1;
	else
		left = right - 1;
	if (!((philo_num % 2) == 0))
	{
		pthread_mutex_unlock(&p->forks[right]);
		printf("\033[0;31mphilo%d : puts left fork down\033[0m\n", philo_num);
		pthread_mutex_unlock(&p->forks[left]);
		printf("\033[0;31mphilo%d : puts right fork down\033[0m\n", philo_num);
	}
	else
	{
		
		pthread_mutex_unlock(&p->forks[left]);
		printf("\033[0;31mphilo%d : puts left fork down\033[0m\n", philo_num);
		pthread_mutex_unlock(&p->forks[right]);
		printf("\033[0;31mphilo%d : puts right fork down\033[0m\n", philo_num);
	}
}

void	ft_eat(t_philostruct *p, int philo_num)
{
	// if (philo_num == 1)
	// 		printf("\033[0;31mje suis en vie\033[0m\n");
	pick_fork(p, philo_num);
	
	pthread_mutex_lock(&p->philo_list[philo_num].philo_locker);
	p->philo_list[philo_num].last_meal = get_good_time();
	p->philo_list[philo_num].num_of_meals++;
	pthread_mutex_unlock(&p->philo_list[philo_num].philo_locker);
	displayer(p, philo_num, "is eating\n");
	usleep(p->time_to_eat * 1000);
	put_fork_down(p, philo_num);
	// printf("last meal = %lu \n, num of meals%d\n", p->philo_list[philo_num].last_meal, p->philo_list[philo_num].num_of_meals);
}

void	ft_sleep(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is sleeping\n");
	usleep(p->time_to_sleep * 1000);
	// displayer(p, philo_num, "is thinking\n");
}

// void	ft_think(t_philostruct *p, int philo_num)
// {
// 	displayer(p, philo_num, "is thinking\n");
// }

void	*ft_routine(void *content)
{
	t_philostruct	*p;
	int 			i;

	p = (t_philostruct *)content;
	i = p->which_philo;
	// printf("%d\n", i);
	// printf("\n%d\n", p->which_philo);
	while (p->can_display != 1) // mettre aussi un compteur dans la struct du philo pour compter le nombre de repas, et faire une fonction qui va check si tous les philos ont fini de manger
	{
		if (!(i % 2))
			usleep(p->time_to_eat * 1000);
		usleep(100);
		ft_eat(p, i);
		ft_sleep(p, i);
		// ft_think(p, i);
	}
	return (NULL);
}

void	philo_launcher(t_philostruct *p)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&p->locker);
	while (p->which_philo < p->num_of_phil)
	{
		usleep(50);
		// printf("%d\n", p->which_philo);
		pthread_create(&p->philo_list[p->which_philo].philo, NULL, &ft_routine, p);
		p->which_philo++;
	}
	pthread_mutex_unlock(&p->locker);
	usleep(10000);
	// pthread_create(&p->reaper, NULL, &reaper, p);
	while (++i < p->num_of_phil)
		pthread_join(p->philo_list[i].philo, NULL);
	// pthread_join(p->reaper, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////

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
		philo_launcher(p);
		// demallocage(p);
	}
	return (0);
}