/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:36:12 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/05/26 13:37:12 by rdel-agu         ###   ########.fr       */
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
	long unsigned			last_meal;
	int						num_of_meals;
	
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
	t_philo						*philo_list;
}								t_philostruct;

// typedef struct		s_philo
// {
// 	int						position;
// 	int						is_eating;
// 	unsigned long long		limit;
// 	unsigned long long		last_eat;
// 	int						lfork;
// 	int						rfork;
// 	int						eat_count;
// 	struct s_state			*state;
// 	pthread_mutex_t			mutex;
// 	pthread_mutex_t			eat_m;
// }							t_philo;

// typedef struct		s_state
// {
// 	int						amount;
// 	unsigned long long		time_to_die;
// 	unsigned long long		time_to_eat;
// 	unsigned long long		time_to_sleep;
// 	int						must_eat_count;

// 	unsigned long long		start;

// 	t_philo					*philos;
// 	pthread_mutex_t			*forks_m;
// 	pthread_mutex_t			write_m;
// 	pthread_mutex_t			somebody_dead_m;
// }							t_state;

#endif