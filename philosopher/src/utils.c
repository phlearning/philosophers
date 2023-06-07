/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:46:40 by pvong             #+#    #+#             */
/*   Updated: 2023/06/02 17:30:11 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_table(t_table *tab)
{
	printf("---------- TABLE ----------\n");
	printf("nb of philo: %d\n", tab->nb_philo);
	printf("time_to_die: %dms\n", (int) tab->time_to_die);
	printf("time_to_eat: %dms\n", (int) tab->time_to_eat);
	printf("time_to_sleep: %dms\n", (int) tab->time_to_sleep);
	if (tab->meals_needed > 0)
		printf("nb_of_meals_needed: %d\n", tab->meals_needed);
	printf("---------- ----- ----------\n");
}

// void	print_message(t_philo *philo, t_table *tab, int message)
// {
// 	long int	time;

// 	time = get_time() - tab->data->time_start;
// 	conv_to_read_time(time, 0);
// 	printf("%d ", philo->id);
// 	if (message == TAKING_FORK)
// 		printf("has taken a fork\n");
// 	if (message == EATING)
// 		printf("is eating\n");
// 	if (message == SLEEPING)
// 		printf("is sleeping\n");
// 	if (message == THINKING)
// 		printf("is thinking\n");
// }

int	print_error(char *str)
{
	printf("%s", str);
	return (-1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

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