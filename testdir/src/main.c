/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/04/19 15:10:52 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#define NB 10

void	*routine(void *data)
{
	t_th *threads;

	threads = data;
	pthread_mutex_lock(&threads->mutex);
	threads->time = get_time();
	conv_to_read_time(threads->time, 0);
	printf(" Hello\n");
	usleep(1000);
	threads->time = get_time();
	conv_to_read_time(threads->time, 0);
	printf(" Ending thread\n");
	pthread_mutex_unlock(&threads->mutex);
	return (0);
}

int	main(void)
{
	t_th	*threads;

	threads = malloc(sizeof(t_th));
	threads->time = get_time();
	pthread_mutex_init(&threads->mutex, NULL);
	conv_to_read_time(threads->time, 1);
	threads->th = malloc(sizeof(pthread_t) * NB);
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