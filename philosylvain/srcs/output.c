/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <synicole@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:42:56 by synicole          #+#    #+#             */
/*   Updated: 2023/05/19 12:42:57 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * This function prints the status of a philosopher based on string parameter.
 *
 * @param philo The philosopher
 * @param status The value representing the current state of the philosopher.
 *
 * @return void
 */
static void	ft_print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", ft_get_time_in_ms() - philo->env->start_time,
		philo->id + 1, str);
}

/**
 * This function writes the status of a philosopher based on the provided
 * status parameter.
 * If the simulation is over and monitoring_report is 0, the function
 * returns without writing anything.
 * It prints the appropriate status message based on
 * the provided status parameter.
 *
 * @param philo The philosopher
 * @param monitoring_report A flag indicating whether the status is
 * a monitoring report (1 - monitoring report, 0 - regular status).
 * @param status The value representing the current state of the philosopher.
 *
 * @return void
 */
void	ft_write_status(t_philo *philo, int monitoring_report, t_status status)
{
	pthread_mutex_lock(&philo->env->write_lock);
	if (ft_is_simulation_over(philo->env) == 1 && monitoring_report == 0)
	{
		pthread_mutex_unlock(&philo->env->write_lock);
		return ;
	}
	if (DEBUG == 1)
	{
		ft_write_status_debug(philo, status);
		pthread_mutex_unlock(&philo->env->write_lock);
		return ;
	}
	if (status == E_DIED)
		ft_print_status(philo, "died");
	else if (status == E_EATING)
		ft_print_status(philo, "is eating");
	else if (status == E_SLEEPING)
		ft_print_status(philo, "is sleeping");
	else if (status == E_THINKING)
		ft_print_status(philo, "is thinking");
	else if (status == E_GOT_FORK_1 || status == E_GOT_FORK_2)
		ft_print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->env->write_lock);
}
