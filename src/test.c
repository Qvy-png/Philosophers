/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:54:43 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/05/23 18:36:56 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int counter;
pthread_mutex_t fourchette;

void* philo_thread(void *arg)
{
	struct timeval before_time, after_time;
    unsigned long i = 0;

    pthread_mutex_lock(&fourchette);
	gettimeofday(&before_time, NULL);
	counter += 1;
    printf("\n Job %d started\n", counter);
    printf("\n Job %d finished\n", counter);
    gettimeofday(&after_time, NULL);
	printf("microseconds : %ld\n", after_time.tv_usec - before_time.tv_usec);
    pthread_mutex_unlock(&fourchette);
    return NULL;
}

int main(void)
{
    int i;
	int j;
    int err;
	pthread_t tid[5];

	i = -1;
	j = -1;
    if (pthread_mutex_init(&fourchette, NULL) != 0)
        return (printf("\n mutex init failed\n"), 1);
    while(++i < 5)
    {
        err = pthread_create(&(tid[i]), NULL, &philo_thread, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
    }
	while (++j < 5)
		pthread_join(tid[j], NULL);
    pthread_mutex_destroy(&fourchette);
    return 0;
}