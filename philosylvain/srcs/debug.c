/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <synicole@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:30:47 by synicole          #+#    #+#             */
/*   Updated: 2023/05/19 14:30:49 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * This function prints the status of a philosopher based on the provided
 * status parameter and the string parameter.
 *
 * @param philo The philosopher whose status is to be printed.
 * @param str The string to be printed.
 * @param status The status code of the philosopher.
 */
static void	ft_print_status_debug(t_philo *philo, char *str, t_status status)
{
	if (status == E_GOT_FORK_1)
		printf("[%10ld]\t%03d\t%s: fork [%d]\n",
			ft_get_time_in_ms() - philo->env->start_time,
			philo->id + 1, str, philo->fork[0]);
	else if (status == E_GOT_FORK_2)
		printf("[%10ld]\t%03d\t%s: fork [%d]\n",
			ft_get_time_in_ms() - philo->env->start_time,
			philo->id + 1, str, philo->fork[1]);
	else
		printf("[%10ld]\t%03d\t%s\n",
			ft_get_time_in_ms() - philo->env->start_time, philo->id + 1, str);
}

/**
 * This function writes the status of a philosopher based on the provided
 * status parameter.
 * It prints the appropriate status message based on
 * the provided status parameter.
 *
 * @param philo The philosopher
 * @param status The value representing the current state of the philosopher.
 *
 * @return void
 */
void	ft_write_status_debug(t_philo *philo, t_status status)
{
	if (status == E_DIED)
		ft_print_status_debug(philo, "died", status);
	else if (status == E_EATING)
		ft_print_status_debug(philo, "is eating", status);
	else if (status == E_SLEEPING)
		ft_print_status_debug(philo, "is sleeping", status);
	else if (status == E_THINKING)
		ft_print_status_debug(philo, "is thinking", status);
	else if (status == E_GOT_FORK_1 || status == E_GOT_FORK_2)
		ft_print_status_debug(philo, "has taken a fork", status);
}

/**
 * This function writes the outcome of the simulation in debug mode.
 * It counts the number of philosophers that have eaten at least the
 * specified number of meals (must_eat_count) and prints the count along with
 * the total number of philosophers.
 *
 * @param env The environment.
 *
 * @return void
 */
void	ft_write_outcome_debug(t_env *env)
{
	unsigned int	i;
	unsigned int	full_count;

	full_count = 0;
	i = 0;
	while (i < env->nb_philos)
	{
		if (env->philosophers[i]->nb_meal_eaten
			>= (unsigned int)env->must_eat_count)
			full_count++;
		i++;
	}
	pthread_mutex_lock(&env->write_lock);
	printf("%d/%d philosophers had at least %d meals.\n",
		full_count, env->nb_philos, env->must_eat_count);
	pthread_mutex_unlock(&env->write_lock);
}
