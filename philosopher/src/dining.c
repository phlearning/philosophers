/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:00:13 by pvong             #+#    #+#             */
/*   Updated: 2023/05/31 18:58:40 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eating(void *arg)
{
	(void) arg;
	t_table *tab;
	
	tab = (t_table *) arg;
	return (0);
}

void	thinking(t_philo *philo, int flag_print)
{
	long int	time;

	pthread_mutex_lock(&philo->meal_mutex);
	time = (philo->tab->time_to_die - (get_time() - philo->time_last_meal))
}

int	game_over(t_table *tab)
{
	int	game_over;

	game_over = 0;
	pthread_mutex_lock(&tab->stop_dining);
	if (tab->game_over = 1)
		game_over = 1;
	pthread_mutex_lock(&tab->stop_dining);
	return (game_over);
}

static void *one_ph(t_philo *philo)
{
	pthread_mutex_lock(&philo->tab->fork_locks[philo->l_fork]);
	print_state(philo, 0, TAKE_FORK_L);
	check_n_sleep(tab, philo->tab->time_to_die);
	print_state(philo, 0, TAKE_FORK_R);
	pthread_mutex_unlock(&philo->tab->fork_locks[philo->l_fork]);
	return (NULL);
}

void	*ph_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (philo->tab->meals_needed == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_last_meal = philo->tab->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	while (get_time() < philo->tab->start_time)
		continue ;
	if (philo->tab->time_to_die == 0)
		return (NULL);
	if (philo->tab->nb_philo == 1)
		return (one_ph(philo));
	else if (philo->id % 2)

}

int	start_dining(t_table *tab)
{
	unsigned int	i;

	tab->start_time  = get_time();
	i = -1;
	while (++i < tab->nb_philo)
	{
		if (pthread_create(&tab->philo[i]->th, NULL, &ph_routine, tab->philo[i]) != 0)
			return (exit_error("Failed to create dining threads\n", tab));
	}
	if (tab->nb_philo > 1)
	{
		if (pthread_create(&tab->monitor, NULL, &monitoring, tab) != 0)
			return (exit_error("Failed to create monitor threads\n", tab));
	}
	return (1);
}