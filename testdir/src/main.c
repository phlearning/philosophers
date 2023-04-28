/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/04/28 17:39:17 by pvong            ###   ########.fr       */
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
	pthread_mutex_unlock(&ph->mutex_eat);
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
	if (!ph->eating && get_time() < ph->death_timer)
	{
		// pthread_mutex_unlock(&ph->mutex_death);
		print_status(ph, DIED);
		return (1);
	}
}

void	*routine(void *data)
{
	int			i;
	t_ph		*ph;
	pthread_t	*th;
	// t_env	*threads;

	// threads = data;
	ph = data;
	// pthread_create(&th, NULL, )
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
	t_env		*env;
	int		i;

	env = malloc(sizeof(t_env));
	init_ph(env);
			// printf("hello\n");
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
