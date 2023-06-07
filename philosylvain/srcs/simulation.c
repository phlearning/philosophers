/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:34:52 by synicole          #+#    #+#             */
/*   Updated: 2023/06/01 14:07:41 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * This function starts the simulation.
 * It creates the threads for the philosophers and the monitoring thread.
 * It also sets the start time of the simulation.
 *
 * @param env The environment structure.
 *
 * @return int 1 if the simulation started successfully, 0 otherwise.
 */
int	ft_start_simulation(t_env *env)
{
	unsigned int	i;

	printf("start simulation\n");
	env->start_time = ft_get_time_in_ms() + (env->nb_philos * 2 * 10);
	i = 0;
	while (i < env->nb_philos)
	{
		if (pthread_create(&env->philosophers[i]->thread,
				NULL, &ft_philo_routine, env->philosophers[i]) != 0)
			return (ft_error_int(MSG_ERR_THREAD, env));
		i++;
	}
	if (env->nb_philos > 1)
		if (pthread_create(&env->monitoring, NULL, &ft_monitoring, env) != 0)
			return (ft_error_int(MSG_ERR_THREAD, env));
	return (1);
}

/**
 * This function is used to delay the start of the simulation.
 * It is used to make sure that all the philosophers are ready to start
 * the simulation at the same time.
 *
 * @param start_time The start time of the simulation.
 *
 * @return void
 */
void	ft_simulation_start_delay(time_t start_time)
{
	while (ft_get_time_in_ms() < start_time)
		continue ;
}

/**
 * This function checks if the simulation is over.
 * It locks the mutex that protects the is_over variable.
 * It returns the value of the is_over variable.
 *
 * @param env The environment structure.
 *
 * @return int 1 if the simulation is over, 0 otherwise.
 */
int	ft_is_simulation_over(t_env *env)
{
	int	is_over;

	is_over = 0;
	pthread_mutex_lock(&env->simulation_stop_lock);
	if (env->is_over == 1)
		is_over = 1;
	pthread_mutex_unlock(&env->simulation_stop_lock);
	return (is_over);
}

/**
 * This function stops the simulation.
 * It joins the threads of the philosophers and the monitoring thread.
 *
 * @param env The environment structure.
 *
 * @return void
 */
void	ft_stop_simulation(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_philos)
	{
		pthread_join(env->philosophers[i]->thread, NULL);
		i++;
	}
	if (env->nb_philos > 1)
		pthread_join(env->monitoring, NULL);
	if (DEBUG == 1 && env->must_eat_count != -1)
		ft_write_outcome_debug(env);
	ft_destroy_mutexes(env);
	ft_free_env(env);
}
