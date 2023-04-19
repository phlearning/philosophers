/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:34:29 by pvong             #+#    #+#             */
/*   Updated: 2023/04/18 11:45:55 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing_2(t_data *data, int ac, char **av, int *err)
{
	if (ac > 5)
	{
		data->nb_of_meals = ft_atoi(av[5]);
		if (data->nb_of_meals <= 0)
			*err = print_error("Nb_of_meals needs to be > 0\n");
	}
	data->time_start = get_time();
	return (0);
}

int	parsing(t_data *data, int ac, char **av)
{
	int	err;

	err = 0;
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo <= 0)
		err = print_error("Nb of philosophers need to be >= 1\n");
	data->nb_forks = data->nb_philo;
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die <= 0)
		err = print_error("Time_to_die needs to be > 0\n");
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat <= 0)
		err = print_error("Time_to_eat needs to be > 0\n");
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep <= 0)
		err = print_error("Time_to_sleep needs to be > 0\n");
	parsing_2(data, ac, av, &err);
	return (err);
}

int	init_philo(t_table *tab)
{
	int	i;

	i = 0;
	tab->philo = malloc(sizeof(t_philo) * (tab->data->nb_philo + 1));
	if (!tab->philo)
		return (-1);
	tab->philo[tab->data->nb_philo + 1] = 0;
	while (i < tab->data->nb_philo)
	{
		tab->philo[i] = malloc(sizeof(t_philo));
		if (!tab->philo[i])
			return (-1);
		tab->philo[i]->id = i;
		tab->philo[i]->l_fork = i;
		tab->philo[i]->l_fork = (i + 1) % tab->data->nb_philo;
		tab->philo[i]->meals_taken = 0;
		tab->philo[i]->time_lim = get_time() \
				+ ((tab->data->time_to_die) * 1000) - tab->data->time_start;
		i++;
	}
	return (0);
}

// int init(t_table *tab, int ac, char **av)
// {
// 	int err;

// 	err = 0;
// 	err = parsing(tab->data, ac, av);
// 	if (err == -1)
// 		return (err);
// 	err = init_philo(tab);
// 	return (err);
// }