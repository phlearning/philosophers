/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:34:29 by pvong             #+#    #+#             */
/*   Updated: 2023/06/02 16:32:52 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_only_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	check_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 0;
	while (++i < ac)
	{
		if (!ft_is_only_digit(av[i]))
		{
			printf("Wrong input must be only positive int: %s\n", av[i]);
			return (0);
		}
		nb = ft_check_max_atoi(av[i]);
		if (nb == -1)
		{
			printf("Integer must be within 0 and 2147483647: %s\n", av[i]);
			return (0);
		}
		if (i == 1 && (nb <= 0 || nb > 200))
		{
			printf("Nb of philo must be within 0 and 200: %s\n", av[i]);
			return (0);
		}
	}
	return (1);
}

// int	parsing_2(t_data *data, int ac, char **av, int *err)
// {
// 	if (ac > 5)
// 	{
// 		data->nb_of_meals = ft_atoi(av[5]);
// 		if (data->nb_of_meals <= 0)
// 			*err = print_error("Nb_of_meals needs to be > 0\n");
// 	}
// 	data->time_start = get_time();
// 	return (0);
// }

// int	parsing(t_data *data, int ac, char **av)
// {
// 	int	err;

// 	err = 0;
// 	data->nb_philo = ft_atoi(av[1]);
// 	if (data->nb_philo <= 0)
// 		err = print_error("Nb of philosophers need to be >= 1\n");
// 	data->nb_forks = data->nb_philo;
// 	data->time_to_die = ft_atoi(av[2]);
// 	if (data->time_to_die <= 0)
// 		err = print_error("Time_to_die needs to be > 0\n");
// 	data->time_to_eat = ft_atoi(av[3]);
// 	if (data->time_to_eat <= 0)
// 		err = print_error("Time_to_eat needs to be > 0\n");
// 	data->time_to_sleep = ft_atoi(av[4]);
// 	if (data->time_to_sleep <= 0)
// 		err = print_error("Time_to_sleep needs to be > 0\n");
// 	parsing_2(data, ac, av, &err);
// 	return (err);
// }
