/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:28 by pvong             #+#    #+#             */
/*   Updated: 2023/03/20 17:29:47 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eating(void *arg)
{

}

void	dining(t_data *philo, int ac)
{
	pthread_t	*th;
	int	i;

	if (ac == 6)
	{
		dining_with_nb_meals(philo);
		return ;
	}
	i = 0;
	th = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!th)
		return ;
	while (i < philo->nb_forks)
	{
		if (pthread_create(&th[i], NULL, &eating, philo != 0))
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
	t_data	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philosophers nb_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep [nb_of_meals_needed]\n");
		return (0);
	}
	philo = malloc(sizeof(t_data));
	if (!philo)
		return (0);
	if (parsing(philo, ac, av) == -1)
	{
		free(philo);
		return (0);
	}
	dining(philo, ac);
	free(philo);
	return (0);
}
