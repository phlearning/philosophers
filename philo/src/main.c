/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:28 by pvong             #+#    #+#             */
/*   Updated: 2023/04/18 11:55:27 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			ft_putstr_fd("Failed to create thread", 2);
		++i;
	}
	i = 0;
	while (i < philo->nb_forks)
	{
		if (pthread_join(th[i], NULL) != 0)
			ft_putstr_fd("Failed to join thread", 2);
		++i;
	}
	return ;
}

/**
 * 
 * @param ac 
 * @param av 
 * @param tab 
 * @return int 
 */
int	init(int ac, char **av, t_table *tab)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo nb_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep [nb_of_meals_needed]\n");
		return (0);
	}
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
	if (init_philo(tab) == -1)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	*tab;

	tab = malloc(sizeof(t_table));
	if (!tab)
		return (0);
	if (init(ac, av, tab) == 0)
		return (exit_error("Failed to init\n", tab));
	print_table((tab->data));
	printf("id of philo: %d\n", tab->philo[4]->id);
	dining(tab->data, ac);
	free_tab(tab);
	return (0);
}
