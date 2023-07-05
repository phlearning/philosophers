/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:46:40 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 13:50:00 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_error(char *str, t_table *tab)
{
	printf("Error :%s", str);
	if (tab)
		free_tab(tab);
	return (EXIT_FAILURE);
}

void	*exit_error2(char *str, t_table *tab)
{
	printf("Error %s", str);
	if (tab)
		free_tab(tab);
	return (0);
}

void	check_n_sleep(t_table *tab, long int sleep_time)
{
	long int	get_up_time;

	get_up_time = get_time() + sleep_time;
	while (get_time() < get_up_time)
	{
		if (game_over(tab))
			break ;
		usleep(100);
	}
}

void	end_mutexes(t_table *tab)
{
	unsigned int	i;

	i = -1;
	while (++i < tab->nb_philo)
	{
		pthread_mutex_destroy(&tab->fork_locks[i]);
		pthread_mutex_destroy(&tab->philo[i]->meal_mutex);
	}
	pthread_mutex_destroy(&tab->print_mutex);
	pthread_mutex_destroy(&tab->stop_dining);
}

void	join_dining_threads(t_table *tab)
{
	unsigned int	i;

	i = -1;
	while (++i < tab->nb_philo)
		pthread_join(tab->philo[i]->th, NULL);
	if (tab->nb_philo > 1)
		pthread_join(tab->monitor, NULL);
	end_mutexes(tab);
	free_tab(tab);
}
