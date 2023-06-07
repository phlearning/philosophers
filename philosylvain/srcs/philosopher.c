/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:27:57 by synicole          #+#    #+#             */
/*   Updated: 2023/06/01 14:30:16 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * This function represents the sleeping action of a philosopher.
 * The philosopher sleeps for the specified sleep_time. If the simulation
 * is over, the philosopher does not sleep.
 *
 * @param env The environment structure.
 * @param sleep_time The time to sleep in milliseconds.
 *
 * @return void * NULL.
 */
static void	ft_philo_sleep(t_env *env, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = ft_get_time_in_ms() + sleep_time;
	while (ft_get_time_in_ms() < wake_up)
	{
		if (ft_is_simulation_over(env))
			break ;
		usleep(100);
	}
}

/**
 * This function represents the eating action of a philosopher.
 * The philosopher locks the two forks they need to eat and then sleeps
 * for the specified time_to_eat. If the simulation is over, the philosopher
 * does not eat. The philosopher then unlocks the two forks and sleeps
 * for the specified time_to_sleep.
 *
 * @param philo The philosopher.
 *
 * @return void * NULL.
 */
static void	ft_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork_locks[philo->fork[0]]);
	ft_write_status(philo, 0, E_GOT_FORK_1);
	pthread_mutex_lock(&philo->env->fork_locks[philo->fork[1]]);
	ft_write_status(philo, 0, E_GOT_FORK_2);
	ft_write_status(philo, 0, E_EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	ft_philo_sleep(philo->env, philo->env->time_to_eat);
	if (ft_is_simulation_over(philo->env) == 0)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->nb_meal_eaten += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	ft_write_status(philo, 0, E_SLEEPING);
	pthread_mutex_unlock(&philo->env->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->env->fork_locks[philo->fork[0]]);
	ft_philo_sleep(philo->env, philo->env->time_to_sleep);
}

/**
 * This function represents the thinking action of a philosopher.
 * The philosopher calculates the time available for thinking based on the
 * time since their last meal and the specified time_to_die and time_to_eat.
 * The function then sleeps for the calculated time and optionally writes
 * the thinking status if silent is set to 0.
 *
 * @param philo The philosopher.
 * @param silent If silent is 1, the philosopher does not write the status.
 *
 * @return void * NULL.
 */
static void	ft_think(t_philo *philo, int silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->env->time_to_die
			- (ft_get_time_in_ms() - philo->last_meal)
			- philo->env->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == 0)
		ft_write_status(philo, 0, E_THINKING);
	ft_philo_sleep(philo->env, time_to_think);
}

/**
 * This function represents the routine for a philosopher when there is only
 * one philosopher in the simulation.
 * The philosopher acquires a fork, writes the status, sleeps for
 * the specified time_to_die duration, writes the status of their death,
 * and releases the acquired fork.
 *
 * @param philo The philosopher.
 *
 * @return void * NULL.
 */
static void	*ft_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork_locks[philo->fork[0]]);
	ft_write_status(philo, 0, E_GOT_FORK_1);
	ft_philo_sleep(philo->env, philo->env->time_to_die);
	ft_write_status(philo, 0, E_DIED);
	pthread_mutex_unlock(&philo->env->fork_locks[philo->fork[0]]);
	return (NULL);
}

/**
 * This function represents the routine of a philosopher thread.
 * It performs the necessary actions for a philosopher during the simulation,
 * such as eating, sleeping, and thinking.
 *
 * @param data The data passed to the thread.
 *
 * @return void* NULL.
 */
void	*ft_philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->env->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->env->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	ft_simulation_start_delay(philo->env->start_time);
	if (philo->env->time_to_die == 0)
		return (NULL);
	if (philo->env->nb_philos == 1)
		return (ft_alone(philo));
	else if (philo->id % 2)
		ft_think(philo, 1);
	while (!ft_is_simulation_over(philo->env))
	{
		ft_eat_sleep(philo);
		ft_think(philo, 0);
	}
	return (NULL);
}
