/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:21:36 by pvong             #+#    #+#             */
/*   Updated: 2023/04/24 13:09:42 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	init_ph(t_env *threads)
{
	int	i;

	i = -1;
	threads->start_time = get_time();
	threads->time = threads->start_time;
	threads->th = malloc(sizeof(pthread_t) * NB);
	pthread_mutex_init(&threads->mutex, NULL);
	threads->ph = malloc(sizeof(t_ph) * NB);
	if (!threads->ph)
		return (-1);
	threads->mutex_forks = malloc(sizeof(pthread_mutex_t) * NB);
	if (!threads->mutex_forks)
		return (-1);
	while (++i < NB)
	{
		threads->ph[i].id = i;
		threads->ph[i].left_fork = i % NB;
		threads->ph[i].right_fork = (i + 1) % NB;
		threads->ph[i].env = threads;
		pthread_mutex_init(&threads->mutex_forks[i], NULL);
	}
	return (0);
}