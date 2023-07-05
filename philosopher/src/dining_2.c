/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:33:11 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 14:08:59 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_ph(t_philo *philo)
{
	pthread_mutex_lock(&philo->tab->fork_locks[philo->l_fork]);
	print_state(philo, 0, TAKE_FORK_L);
	check_n_sleep(philo->tab, philo->tab->time_to_die);
	print_state(philo, 0, DIED);
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
		thinking(philo, 1);
	while (!(game_over(philo->tab)))
	{
		eating(philo);
		thinking(philo, 0);
	}
	return (NULL);
}

int	start_dining(t_table *tab)
{
	unsigned int	i;

	tab->start_time = get_time();
	i = -1;
	while (++i < tab->nb_philo)
	{
		if (pthread_create(&tab->philo[i]->th, NULL, \
			&ph_routine, tab->philo[i]) != 0)
			return (exit_error("Failed to create dining threads\n", tab));
	}
	if (tab->nb_philo > 1)
	{
		if (pthread_create(&tab->monitor, NULL, &monitoring, tab) != 0)
			return (exit_error("Failed to create monitor threads\n", tab));
	}
	return (1);
}

void	thinking(t_philo *philo, int flag_print)
{
	long int	time;

	pthread_mutex_lock(&philo->meal_mutex);
	time = (philo->tab->time_to_die - (get_time() - philo->time_last_meal) \
			- philo->tab->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	printf("TIME: %ld\n", time);
	if (time < 0)
		time = 0;
	if (time == 0 && flag_print == 1)
		time = 1;
	if (time > 600)
		time = 200;
	if (flag_print == 0)
		print_state(philo, 0, THINKING);
	check_n_sleep(philo->tab, time);
}

/* void	thinking(t_philo *philo, int flag_print)
{
	if (flag_print == 0)
		print_state(philo, 0, THINKING);
	check_n_sleep(philo->tab, 0);
} */
