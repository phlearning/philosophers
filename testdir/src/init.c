/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:21:36 by pvong             #+#    #+#             */
/*   Updated: 2023/04/28 17:57:12 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	init_mutex(t_env *env)
{
	int	i;

	i = -1;
	pthread_mutex_init(&env->mutex, NULL);
	while (i++ < NB)
	{
		pthread_mutex_init(&env->mutex_forks[i], NULL);
		pthread_mutex_init(&env->ph[i].mutex_death, NULL);
		pthread_mutex_init(&env->ph[i].mutex_eat, NULL);
	}
	return (0);
}

int	init_ph(t_env *env)
{
	int	i;

	i = -1;
	env->start_time = get_time();
	env->time = env->start_time;
	env->th = malloc(sizeof(pthread_t) * NB);
	pthread_mutex_init(&env->mutex, NULL);
	env->ph = malloc(sizeof(t_ph) * NB);
	if (!env->ph)
		return (-1);
	env->mutex_forks = malloc(sizeof(pthread_mutex_t) * NB);
	if (!env->mutex_forks)
		return (-1);
	while (++i < NB)
	{
		env->ph[i].id = i;
		env->ph[i].left_fork = i % NB;
		env->ph[i].right_fork = (i + 1) % NB;
		env->ph[i].env = env;
		pthread_mutex_init(&env->mutex_forks[i], NULL);
	}
	return (0);
}