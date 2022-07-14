/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:24:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/14 19:04:01 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	micro_sleep(long unsigned time)
{
	long unsigned	actual;

	actual = get_good_time();
	while ((get_good_time() - actual) * 1000 < time)
		usleep(50);
}

long unsigned	get_good_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	displayer(t_philostruct *p, int num_of_phil, char *action)
{
	long unsigned	time;
	// int 			disp;

	pthread_mutex_lock(&p->locker);
	// disp = p->can_display;
	
	time = get_good_time() - p->start;
	pthread_mutex_lock(&p->is_talking);
	if (p->can_display == 0)
	{
		printf("%lu %d %s", time, num_of_phil, action);
	}
	pthread_mutex_unlock(&p->is_talking);
	pthread_mutex_unlock(&p->locker);
}

void	*reaper(void *content)
{
	t_philostruct	*p;
	int				i;
	long unsigned	time_result;
	int				quit;

	p = (t_philostruct *)content;
	i = 0;
	quit = 0;
	time_result = 0;
	while (quit == 0)
	{
		i = 0;
		while (i < p->num_of_phil && p->philo_list[i].last_meal > 0)
		{
			if (p->philo_list[i].last_meal == 0)
				i++;
			pthread_mutex_lock(&p->philo_list[i].philo_locker);
			time_result = get_good_time() - p->philo_list[i].last_meal;
			// printf("je suis philo %d, %lu - %lu = %lu\n", i + 1, get_good_time(), p->philo_list[i].last_meal, get_good_time() - p->philo_list[i].last_meal);
			pthread_mutex_unlock(&p->philo_list[i].philo_locker);
			// printf("\033[0;32mscan me : %lu - %lu\033[0m\n", time_result, p->time_to_die);
			if (time_result >= p->time_to_die)
			{
				pthread_mutex_lock(&p->locker);
				if (p->can_display == 0)
				{
					p->can_display = 1;
					printf("\033[0;32m%lu %d has died\033[0m\n", get_good_time() - p->start, i + 1);
				}
				pthread_mutex_unlock(&p->locker);
				quit++;
			}
			i++;
		}
	}
	return (NULL);
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
	pthread_mutex_lock(&p->locker);
	if (p->can_display == 0)
		p->can_display = 1;
	pthread_mutex_unlock(&p->locker);
	return (NULL);
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
	if (philo_num % 2 == 0 || philo_num - 1 == p->num_of_phil)
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
	if (philo_num % 2 == 0 || philo_num - 1 == p->num_of_phil)
	{
		pthread_mutex_unlock(&p->forks[right]);
		pthread_mutex_unlock(&p->forks[left]);
		// printf("je suis %d et je viens de poser mes deux fourchettes %d\n", philo_num, left + 1);
	}
	else
	{
		pthread_mutex_unlock(&p->forks[left]);
		pthread_mutex_unlock(&p->forks[right]);
		// printf("je suis %d et je viens de poser mes deux fourchettes %d\n", philo_num, left + 1);
	}
}

void	ft_eat(t_philostruct *p, int philo_num)
{
	pick_fork(p, philo_num);
	pthread_mutex_lock(&p->philo_list[philo_num - 1].philo_locker);
	p->philo_list[philo_num - 1].last_meal = get_good_time();
	p->philo_list[philo_num - 1].num_of_meals += 1;
	pthread_mutex_unlock(&p->philo_list[philo_num - 1].philo_locker);
	displayer(p, philo_num, "is eating\n");
	micro_sleep(p->time_to_eat * 1000);
	put_fork_down(p, philo_num);
	// printf("last meal = %lu \n, num of meals%d\n", p->philo_list[philo_num].last_meal, p->philo_list[philo_num].num_of_meals);
}

void	ft_sleep(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is sleeping\n");
	micro_sleep(p->time_to_sleep * 1000);
}

void	ft_think(t_philostruct *p, int philo_num)
{
	displayer(p, philo_num, "is thinking\n");
}

void	*ft_routine(void *content)
{
	t_philostruct	*p;
	int				i;
	// int				disp;
	int				bricolage;

	p = (t_philostruct *)content;
	pthread_mutex_lock(&p->locker);
	i = s()->which_philo;
	bricolage = p->can_display;
	pthread_mutex_unlock(&p->locker);
	// bricolage = 0;
	while (bricolage != 1) // mettre aussi un compteur dans la struct du philo pour compter le nombre de repas, et faire une fonction qui va check si tous les philos ont fini de manger
	{
		pthread_mutex_lock(&p->locker);
		bricolage = p->can_display;
		pthread_mutex_unlock(&p->locker);
		ft_eat(p, i);
		ft_sleep(p, i);
		ft_think(p, i);
	}
	return (NULL);
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
		while (s()->which_philo < p->num_of_phil)
		{
			usleep(50);	
			pthread_mutex_lock(&p->locker);
			pthread_create(&p->philo_list[s()->which_philo].philo, NULL, &ft_routine, p);
			s()->which_philo = s()->which_philo + 1;
			pthread_mutex_unlock(&p->locker);
		}
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

////////////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char **argv)
{
	t_philostruct	*p;

	p = malloc(sizeof(t_philostruct));
	if (!p)
		return (0);
	if (argc == 5 || argc == 6)
	{
		init(p, argv);
		philo_creator(p);
		philo_launcher(p);
		demallocage(p);
	}
	free(p);
	return (0);
}
