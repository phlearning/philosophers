/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/04/27 16:14:59 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	eating(t_ph *ph)
{
	pthread_mutex_lock(&ph->mutex_eat);
	print_status(ph, EATING);
	usleep(T2E);
	pthread_mutex_unlock(&ph->mutex_eat);
}

void thinking(t_ph *ph)
{
	(void) ph;
	print_status(ph, THINKING);
	usleep(T2T);
}

void	*routine(void *data)
{
	int		i;
	t_ph	*ph;
	// t_env	*threads;

	// threads = data;
	ph = data;
	pthread_mutex_lock(&ph->env->mutex);
	i = -1;
	while (++i < 1)
	{
		take_fork(ph);
		eating(ph);
		clean_fork(ph);
		thinking(ph);
	}
	printf(" Ending thread\n");
	pthread_mutex_unlock(&ph->env->mutex);
	return (0);
}

int	main(void)
{
	t_env	*threads;
	int		i;

	threads = malloc(sizeof(t_env));
	init_ph(threads);
			// printf("hello\n");
	print_time(threads->start_time, 1);
	i = -1;
	while (++i < NB)
	{
		if (pthread_create(&threads->th[i], NULL, &routine, &threads->ph[i]) != 0)
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
