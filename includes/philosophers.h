/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:36:12 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/05 00:00:40 by qvy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
// # include <libft.h>

# define EAT 	0
# define SLEEP 1
# define FORK 	2
# define THINK	3
# define DIED 	4
# define OVER 	5

typedef struct s_philo
{
	int						philo_num;
	pthread_t				philo;
	long unsigned			last_meal;
	int						num_of_meals;
	pthread_mutex_t			philo_locker;
	
}							t_philo;

typedef struct s_philostruct
{
	int							num_of_phil;
	long unsigned				time_to_die;
	long unsigned				time_to_eat;
	long unsigned				time_to_sleep;
	int							num_of_meals;
	int							can_display;
	pthread_mutex_t 			*forks;
	pthread_mutex_t				locker;
	pthread_mutex_t				is_talking;
	pthread_t					reaper;
	t_philo						*philo_list;
}								t_philostruct;

int	ft_atoi(const char *str);
void	demallocage(t_philostruct *p);
void	ft_exit(t_philostruct *p, char *message);

#endif