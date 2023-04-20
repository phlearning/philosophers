/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/04/20 15:55:44 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	take_fork(t_th *th, int i)
{
	pthread_mutex_lock(&th->mutex_forks[th->ph[i].left_fork % NB]);
	pthread_mutex_lock(&th->mutex_forks[(th->ph[i].right_fork) % NB]);
	print_status(th, TAKING_FORK, i);
}

void	clean_fork(t_th *th, int i)
{
	pthread_mutex_unlock(&th->mutex_forks[th->ph[i].left_fork % NB]);
	pthread_mutex_unlock(&th->mutex_forks[(th->ph[i].right_fork) % NB]);
}

void	eating(t_th *th, int i)
{
	pthread_mutex_lock(&th->)
}

void	*routine(void *data)
{
	t_th	*threads;
	int		i;

	threads = data;
	pthread_mutex_lock(&threads->mutex);
	i = -1;
	while (++i < NB)
	{
		take_fork(threads, i);
		
		clean_fork(threads, i);
	}
	usleep(1000);
	printf(" Ending thread\n");
	pthread_mutex_unlock(&threads->mutex);
	return (0);
}

int	main(void)
{
	t_th	*threads;
	int		i;

	threads = malloc(sizeof(t_th));
	init_ph(threads);
	print_time(threads->time, 1);
	print_time(threads->start_time, 1);
	i = -1;
	while (++i < NB)
	{
		if (pthread_create(&threads->th[i], NULL, &routine, threads) != 0)
			return (i);
	}
	i = -1;
	while (++i < NB)
	{
		if (pthread_join(threads->th[i], NULL) != 0)
			return (i);
	}
	pthread_mutex_destroy(&threads->mutex);
	return (0);
}