/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:00:13 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 13:40:37 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->tab->fork_locks[philo->l_fork]);
	print_state(philo, 0, TAKE_FORK_L);
	pthread_mutex_lock(&philo->tab->fork_locks[philo->r_fork]);
	print_state(philo, 0, TAKE_FORK_R);
}

void	clean_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->tab->fork_locks[philo->l_fork]);
	pthread_mutex_unlock(&philo->tab->fork_locks[philo->r_fork]);
}

void	eating(t_philo *philo)
{
	take_fork(philo);
	print_state(philo, 0, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	check_n_sleep(philo->tab, philo->tab->time_to_eat);
	if (game_over(philo->tab) == 0)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_taken++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	print_state(philo, 0, SLEEPING);
	clean_fork(philo);
	check_n_sleep(philo->tab, philo->tab->time_to_sleep);
}

int	game_over(t_table *tab)
{
	int	game_over;

	game_over = 0;
	pthread_mutex_lock(&tab->stop_dining);
	if (tab->game_over == 1)
		game_over = 1;
	pthread_mutex_unlock(&tab->stop_dining);
	return (game_over);
}
