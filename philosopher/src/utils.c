/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:46:40 by pvong             #+#    #+#             */
/*   Updated: 2023/04/18 11:01:39 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_table(t_data *philo)
{
	printf("---------- TABLE ----------\n");
	printf("nb of philo: %d\n", philo->nb_philo);
	printf("death timer: %dms\n", philo->time_to_die);
	printf("eat time: %dms\n", philo->time_to_eat);
	printf("sleep time: %dms\n", philo->time_to_sleep);
	if (philo->nb_of_meals > 0)
		printf("nb_of_meals: %d\n", philo->nb_of_meals);
	printf("time_start: ");
	conv_to_read_time(philo->time_start, 1);
	printf("---------- ----- ----------\n");
}

void	print_message(t_philo *philo, t_table *tab, int message)
{
	long int	time;

	time = get_time() - tab->data->time_start;
	conv_to_read_time(time, 0);
	printf("%d ", philo->id);
	if (message == TAKING_FORK)
		printf("has taken a fork\n");
	if (message == EATING)
		printf("is eating\n");
	if (message == SLEEPING)
		printf("is sleeping\n");
	if (message == THINKING)
		printf("is thinking\n");
}

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
	printf("Error %s", str);
	free_tab(tab);
	return (0);
}