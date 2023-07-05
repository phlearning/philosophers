/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:39:48 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 13:31:26 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*init_forks(t_table *tab)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * tab->nb_philo);
	if (!forks)
		return (exit_error2("Failed to malloc mutex forks\n", tab));
	i = -1;
	while (++i < tab->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (exit_error2("Failed to init mutex forks\n", tab));
	}
	return (forks);
}

int	init_mutex(t_table *tab)
{
	tab->fork_locks = init_forks(tab);
	if (!tab->fork_locks)
		return (0);
	if (pthread_mutex_init(&tab->stop_dining, 0) != 0)
		return (exit_error("Failed to init mutex stop\n", tab));
	if (pthread_mutex_init(&tab->print_mutex, 0) != 0)
		return (exit_error("Failed to init print mutex\n", tab));
	return (1);
}

t_philo	**init_philo(t_table *tab)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * tab->nb_philo);
	if (!philos)
		return (exit_error2("Failed to malloc philos\n", tab));
	i = -1;
	while (++i < tab->nb_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (exit_error2("Failed to malloc philos[i]", tab));
		if (pthread_mutex_init(&philos[i]->meal_mutex, 0) != 0)
			return (exit_error2("Failed to init meal mutex\n", tab));
		philos[i]->tab = tab;
		philos[i]->id = i;
		philos[i]->meals_taken = 0;
		philos[i]->l_fork = i;
		philos[i]->r_fork = (i + 1) % tab->nb_philo;
	}
	return (philos);
}

t_table	*init_tab(int ac, char **av)
{
	t_table	*tab;

	tab = malloc(sizeof(t_table));
	if (!tab)
		return (exit_error2("Failed to init tab\n", tab));
	tab->nb_philo = ft_check_max_atoi(av[1]);
	tab->time_to_die = ft_check_max_atoi(av[2]);
	tab->time_to_eat = ft_check_max_atoi(av[3]);
	tab->time_to_sleep = ft_check_max_atoi(av[4]);
	tab->game_over = 0;
	tab->meals_needed = -1;
	if (ac == 6)
		tab->meals_needed = ft_check_max_atoi(av[5]);
	print_table(tab);
	tab->philo = init_philo(tab);
	if (!tab->philo)
		return (exit_error2("Failed to init philos\n", tab));
	if (!init_mutex(tab))
		return (exit_error2("Failed to init mutex\n", tab));
	return (tab);
}
