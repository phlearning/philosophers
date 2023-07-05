/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:37:07 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 13:58:32 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_philo_dead(t_philo *philo)
{
	long int	time;

	time = get_time();
	if ((time - philo->time_last_meal) >= philo->tab->time_to_die)
	{
		pthread_mutex_lock(&philo->tab->stop_dining);
		philo->tab->game_over = 1;
		pthread_mutex_unlock(&philo->tab->stop_dining);
		print_state(philo, 1, DIED);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	return (0);
}

int	check_meals_n_death(t_table *tab)
{
	unsigned int	i;
	int				meals_reached_flag;

	meals_reached_flag = 1;
	i = -1;
	while (++i < tab->nb_philo)
	{
		pthread_mutex_lock(&tab->philo[i]->meal_mutex);
		if (is_philo_dead(tab->philo[i]))
			return (1);
		if (tab->meals_needed != -1)
			if ((tab->philo[i]->meals_taken) \
				< tab->meals_needed)
				meals_reached_flag = 0;
		pthread_mutex_unlock(&tab->philo[i]->meal_mutex);
	}
	if (tab->meals_needed != -1 && meals_reached_flag == 1)
	{
		pthread_mutex_lock(&tab->stop_dining);
		tab->game_over = 1;
		pthread_mutex_unlock(&tab->stop_dining);
		return (1);
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_table	*tab;

	tab = (t_table *) data;
	if (tab->meals_needed == 0)
		return (NULL);
	pthread_mutex_lock(&tab->stop_dining);
	tab->game_over = 0;
	pthread_mutex_unlock(&tab->stop_dining);
	while (get_time() < tab->start_time)
		continue ;
	while (1)
	{
		if (check_meals_n_death(tab) == 1)
			return (NULL);
		usleep(1000);
	}
}
