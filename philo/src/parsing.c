/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:34:29 by pvong             #+#    #+#             */
/*   Updated: 2023/03/20 16:28:48 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *str)
{
	printf("%s", str);
	return (-1);
}

int	parsing_2(t_data *philo, int ac, char **av, int *err)
{
	if (ac > 5)
	{
		philo->nb_of_meals = ft_atoi(av[5]);
		if (philo->nb_of_meals <= 0)
			*err = print_error("Nb_of_meals needs to be > 0\n");
	}
	if (gettimeofday(&philo->time, NULL) == -1)
	{
		perror("Error");
		*err = -1;
	}
	return (0);
}

int	parsing(t_data *philo, int ac, char **av)
{
	int	err;

	err = 0;
	philo->nb_philo = ft_atoi(av[1]);
	if (philo->nb_philo <= 0)
		err = print_error("Nb of philosophers need to be >= 1\n");
	philo->nb_forks = philo->nb_philo;
	philo->time_to_die = ft_atoi(av[2]);
	if (philo->time_to_die <= 0)
		err = print_error("Time_to_die needs to be > 0\n");
	philo->time_to_eat = ft_atoi(av[3]);
	if (philo->time_to_eat <= 0)
		err = print_error("Time_to_eat needs to be > 0\n");
	philo->time_to_sleep = ft_atoi(av[4]);
	if (philo->time_to_sleep <= 0)
		err = print_error("Time_to_sleep needs to be > 0\n");
	parsing_2(philo, ac, av, &err);
	return (err);
}
