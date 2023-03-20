/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:28 by pvong             #+#    #+#             */
/*   Updated: 2023/03/20 15:49:02 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	dining(t_philo *philo, int ac)
// {
// 	pthread_mutex_t	mutex;
// }

/* Les philosophes doivent prendre 4 arguments (+ 1 optionnel);
	- number_of_philosophers
	- time_to_die
	- time_to_eat
	- time_to_sleep
	- [number_of_times_each_philosopher_must_eat]*/
int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philosophers nb_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep [nb_of_meals_needed]\n");
		return (0);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	if (parsing(philo, ac, av) == -1)
	{
		free(philo);
		return (0);
	}
	// dining(philo, ac);
	free(philo);
	return (0);
}
