/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/05/01 16:41:12 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	eating(t_ph *ph)
{
	pthread_mutex_lock(&ph->mutex_eat);
	ph->eating = 1;
	ph->death_timer = get_time() + T2D;
	print_status(ph, EATING);
	usleep(T2E * 1000);
	ph->eating = 0;
	pthread_mutex_unlock(&ph->env->mutex);
	// pthread_mutex_unlock(&ph->mutex_eat);
}

void thinking(t_ph *ph)
{
	(void) ph;
	print_status(ph, THINKING);
	usleep(T2T * 1000);
}

void	*monitor(void *data)
{
	t_ph	*ph;

	ph = data;
	pthread_mutex_lock(&ph->mutex_death);
	if (!ph->eating && get_time() < ph->death_timer)
	{
		pthread_mutex_unlock(&ph->mutex_death);
		print_status(ph, DIED);
		return ((void *) 1);
	}
	usleep(1000);
	return (0);
}

void	*routine(void *data)
{
	int			i;
	t_ph		*ph;
	uint64_t tid;
	pthread_threadid_np(NULL, &tid);
	// t_env	*threads;

	// threads = data;
	ph = data;
	// if (pthread_create(&th, NULL, &monitor, &ph) != 0)
	// 	return ((void *) 1);
	if (ph->id % 2 == 0)
		usleep(T2E * 1000);
	pthread_mutex_lock(&ph->mutex);
	i = -1;
	while (1)
	{
		take_fork(ph);
		eating(ph);
		clean_fork(ph);
		thinking(ph);
	}
	printf(" Ending thread %llu\n", tid);
	pthread_mutex_unlock(&ph->mutex);
	return (0);
}

int	main(void)
{
	t_env		*env;
	int			i;

	env = malloc(sizeof(t_env));
	init_ph(env);
	print_time(env->start_time, 1);
	i = -1;
	while (++i < NB)
	{
		if (pthread_create(&env->th[i], NULL, &routine, &env->ph[i]) != 0)
			return (i);
	}
	i = -1;
	while (++i < NB)
	{
		if (pthread_join(env->th[i], NULL) != 0)
			return (i);
	}
	pthread_mutex_destroy(&env->mutex);
	return (0);
}
