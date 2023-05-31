/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:17:00 by pvong             #+#    #+#             */
/*   Updated: 2023/05/31 15:02:51 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	eating(t_ph *ph)
{
	pthread_mutex_lock(&ph->mutex);
	ph->eating = 1;
	ph->last_meal_time = get_time();
	ph->death_timer = ph->last_meal_time + T2D;
	print_status(ph, EATING);
	usleep(T2E * 1000);
	ph->amount_eatten++;
	ph->eating = 0;
	// pthread_mutex_unlock(&ph->env->mutex);
	pthread_mutex_unlock(&ph->mutex);
}

void thinking(t_ph *ph)
{
	(void) ph;
	print_status(ph, THINKING);
	usleep(T2T * 1000);
}

/* static void	*monitor(void *data)
{
	t_ph	*ph;
	int		i;
	uint64_t	tid;

	pthread_threadid_np(NULL, &tid);
	i = 0;
	ph = (t_ph *) data;
	while (1)
	{
		// pthread_mutex_lock(&ph->mutex);
		printf("\ttid [%lld] \t monitor death_timer[%d]: %lld\t get_time() %ld\n", tid, i, \
			ph->death_timer, get_time());
		printf("eating ? %d\n", ph->eating);
		if (get_time() > ph->death_timer)
		{
			ph->env->dead = 1;
			// pthread_mutex_unlock(&ph->mutex);
			print_status(ph, DIED);
			// exit(EXIT_SUCCESS);
			return ((void *) 1);
		}
		// pthread_mutex_unlock(&ph->mutex);
		// printf("\tHello last_meal[%d] \t%lld\n", i, ph->last_meal_time);
		// sleep(1);
		usleep(T2E * 1000);
		i++;
	}
} */

/* void	*routine(void *data)
{
	t_ph		*ph;
	// pthread_t	th;
	// uint64_t	tid;
	
	// pthread_threadid_np(NULL, &tid);
	ph = (t_ph *)data;
	ph->last_meal_time = get_time();
	ph->death_timer = ph->last_meal_time + T2D;
	// if (pthread_create(&th, NULL, &monitor, &ph) != 0)
	// 	return ((void *) 1);
	// pthread_detach(th);
	// if (ph->id % 2 == 0)
		// usleep(T2E * 1000);
	pthread_mutex_lock(&ph->mutex);
	while (1)
	{
		take_fork(ph);
		eating(ph);
		clean_fork(ph);
		thinking(ph);
	}
	pthread_mutex_unlock(&ph->mutex);
	return (NULL);
} */

void	*routine(void *philo_v)
{
	t_ph			*philo;
	// pthread_t		tid;

	philo = (t_ph *) philo_v;
	philo->last_meal_time = get_time();
	philo->death_timer = philo->last_meal_time + T2D;
	while (1)
	{
		take_fork(philo);
	printf("hello\n");
		eating(philo);
		clean_fork(philo);
		print_status(philo, THINKING);
	}
	return (0);
}

int	create_threads(t_env *env)
{
	int			i;
	pthread_t	th;
	void		*ph;

	env->start_time = get_time();
	i = 0;
	while (i < NB)
	{
		ph = (void *)(&env->ph[i]);
		if (pthread_create(&th, NULL, &routine, ph) != 0)
			return (ft_error("Couldn't create threads\n"));
		pthread_detach(th);
		usleep(100);
		i++;
	}
	return (0);
}

/* int	join_threads(t_env *env)
{
	(void) env;
	int		i;

	i = -1;
	while (++i < NB)
	{
		if (pthread_join(env->th[i], NULL) ! 0)
			return (i);
	}
} */

int	main(void)
{
	t_env		*env;

	init(&env);
	print_time(env.start_time, 1);
	create_threads(&env);
	pthread_mutex_lock(&env.someone_died);
	pthread_mutex_unlock(&env.someone_died);
	clear_env(&env);
	return (0);
}
