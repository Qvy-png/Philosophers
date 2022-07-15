/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:36:12 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/07/15 03:51:08 by qvy              ###   ########.fr       */
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

typedef struct s_singleton
{
	int							which_philo;
}								t_singleton;

typedef struct s_philo
{
	int							philo_num;
	pthread_t					philo;
	long unsigned				last_meal;
	int							num_of_meals;
	pthread_mutex_t				philo_locker;
	int							can_sleep;
	int							can_think;
}								t_philo;

typedef struct s_philostruct
{
	int							num_of_phil;
	long unsigned				start;
	long unsigned				time_to_die;
	long unsigned				time_to_eat;
	long unsigned				time_to_sleep;
	int							num_of_meals;
	int							can_display;
	int							which_philo;
	int							done;
	pthread_mutex_t				*forks;
	pthread_mutex_t				locker;
	pthread_mutex_t				is_talking;
	pthread_t					reaper;
	pthread_t					grailleur;
	t_philo						*philo_list;
}								t_philostruct;

t_singleton						*s(void);

int								ft_atoi(const char *str);

void							*reaper(void *content);
void							*grailleur(void *content);
void							*ft_routine(void *content);
void							init_mutex(t_philostruct *p);
void							demallocage(t_philostruct *p);
void							micro_sleep(long unsigned time);
void							philo_creator(t_philostruct *p);
void							philo_launcher(t_philostruct *p);
void							init(t_philostruct *p, char **argv);
void							ft_eat(t_philostruct *p, int philo_num);
void							ft_exit(t_philostruct *p, char *message);
void							ft_think(t_philostruct *p, int philo_num);
void							ft_sleep(t_philostruct *p, int philo_num);
void							displayer(t_philostruct *p, int num_of_phil,
									char *action);
void							pick_fork(t_philostruct *p, int philo_num);
void							put_fork_down(t_philostruct *p, int philo_num);

long unsigned					get_good_time(void);

#endif