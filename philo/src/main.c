/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:28 by pvong             #+#    #+#             */
/*   Updated: 2023/03/22 11:29:38 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eating(void *arg)
{
	(void) arg;
	return (0);
}

void	dining(t_data *philo, int ac)
{
	pthread_t	*th;
	int			i;
	(void) ac;

	// if (ac == 6)
	// {
	// 	dining_with_nb_meals(philo);
	// 	return ;
	// }
	i = 0;
	th = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!th)
		return ;
	while (i < philo->nb_forks)
	{
		if (pthread_create(&th[i], NULL, &eating, philo) != 0)
			perror("Failed to create thread");
		++i;
	}
	i = 0;
	while (i < philo->nb_forks)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		++i;
	}
	return ;
}

/* Les philosophes doivent prendre 4 arguments (+ 1 optionnel);
	- number_of_philosophers
	- time_to_die
	- time_to_eat
	- time_to_sleep
	- [number_of_times_each_philosopher_must_eat]*/
int	main(int ac, char **av)
{
	t_table *tab;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philosophers nb_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep [nb_of_meals_needed]\n");
		return (0);
	}
	tab = malloc(sizeof(t_table));
	if (!tab)
		return (0);
	tab->data = malloc(sizeof(t_data));
	if (!tab->data)
	{
		free(tab);
		return (0);
	}
	if (parsing(tab->data, ac, av) == -1)
	{
		free_tab(tab);
		return (0);
	}
	print_table((tab->data));
	dining(tab->data, ac);
	free_tab(tab);
	return (0);
}
