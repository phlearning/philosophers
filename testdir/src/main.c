/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/04/20 12:13:22 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#define NB 10

void	print_status(t_th *th, int message)
{
	th->time = get_time();
	print_time(th->time, NO_NL);
	printf(" Philosopher ");
	if (message == TAKING_FORK)
		printf("has taken a fork\n");
	if (message == EATING)
		printf("is eating\n");
	if (message == SLEEPING)
		printf("sleeping\n");
	if (message == THINKING)
		printf("is thinking\n");
}

void	*routine(void *data)
{
	t_th *threads;

	threads = data;
	pthread_mutex_lock(&threads->mutex);
	print_status(threads, TAKING_FORK);
	usleep(1000);
	threads->time = get_time();
	print_time(threads->time, 0);
	printf(" Ending thread\n");
	pthread_mutex_unlock(&threads->mutex);
	return (0);
}

int	init_ph(t_th *threads)
{
	threads->time = get_time();
	threads->th = malloc(sizeof(pthread_t) * NB);
	pthread_mutex_init(&threads->mutex, NULL);
	for (int i = 0; i < NB; i++)
		threads->id = i;
	return (0);
}

int	main(void)
{
	t_th	*threads;

	threads = malloc(sizeof(t_th));
	init_ph(threads);
	print_time(threads->time, 1);
	for (int i = 0; i < NB; i++)
	{
		if (pthread_create(&threads->th[i], NULL, &routine, threads) != 0)
			return (i);
	}
	for (int i = 0; i < NB; i++)
	{
		if (pthread_join(threads->th[i], NULL) != 0)
			return (i);
	}
	pthread_mutex_destroy(&threads->mutex);
	return (0);
}