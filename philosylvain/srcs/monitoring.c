/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <synicole@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:07:30 by synicole          #+#    #+#             */
/*   Updated: 2023/05/19 12:07:32 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * This function sets the simulation stop flag to the is_over value.
 *
 * @param env The environment structure.
 * @param is_over The value to set the simulation stop flag to.
 *
 * @return void
 */
static void	ft_set_simulation_stop_flag(t_env *env, int is_over)
{
	pthread_mutex_lock(&env->simulation_stop_lock);
	env->is_over = is_over;
	pthread_mutex_unlock(&env->simulation_stop_lock);
}

/**
 * This function checks if a philosopher needs to be killed based on
 * the time elapsed since their last meal and the specified time_to_die.
 * If the elapsed time exceeds the time_to_die, it sets the simulation stop flag,
 * writes the death status of the philosopher, unlocks the meal_time_lock mutex,
 * and returns 1. Otherwise, it returns 0.
 *
 * @param philo The philosopher.
 *
 * @return int 1 if the philosopher needs to be killed, otherwise returns 0.
 */
static int	ft_kill_philo(t_philo *philo)
{
	time_t	time;

	time = ft_get_time_in_ms();
	if ((time - philo->last_meal) >= philo->env->time_to_die)
	{
		ft_set_simulation_stop_flag(philo->env, 1);
		ft_write_status(philo, 1, E_DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (1);
	}
	return (0);
}

/**
 * This function checks if the end condition of the simulation is reached.
 * It iterates over the philosophers, checks if any philosopher needs
 * to be killed, and verifies if all philosophers have eaten enough meals
 * based on the must_eat_count.
 * If the end condition is met, it sets the simulation stop flag and returns 1.
 *
 * @param env The environment structure.
 *
 * @return int 1 if the end condition is reached, otherwise returns 0.
 */
static int	ft_is_end_condition_reached(t_env *env)
{
	unsigned int	i;
	int				all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < env->nb_philos)
	{
		pthread_mutex_lock(&env->philosophers[i]->meal_time_lock);
		if (ft_kill_philo(env->philosophers[i]))
			return (1);
		if (env->must_eat_count != -1)
			if (env->philosophers[i]->nb_meal_eaten
				< (unsigned int)env->must_eat_count)
				all_ate_enough = 0;
		pthread_mutex_unlock(&env->philosophers[i]->meal_time_lock);
		i++;
	}
	if (env->must_eat_count != -1 && all_ate_enough == 1)
	{
		ft_set_simulation_stop_flag(env, 1);
		return (1);
	}
	return (0);
}

/**
 * This function represents the monitoring thread of the simulation.
 * It continuously checks the end conditions of the simulation
 * and sleeps for a short period.
 * If the must_eat_count is 0, the monitoring thread returns immediately.
 *
 * @param data The data passed to the thread.
 *
 * @return void* NULL.
 */
void	*ft_monitoring(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	if (env->must_eat_count == 0)
		return (NULL);
	ft_set_simulation_stop_flag(env, 0);
	ft_simulation_start_delay(env->start_time);
	while (1)
	{
		if (ft_is_end_condition_reached(env) == 1)
			return (NULL);
		usleep(1000);
	}
}
