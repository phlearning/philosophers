/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:09:05 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 13:50:22 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

void	print_philo(t_philo *philo, char *str, int newline)
{
	conv_to_read_time(get_time() - philo->tab->start_time, 0);
	printf(" %d %s", philo->id + 1, str);
	if (newline == 1)
		printf("\n");
}

void	print_state(t_philo *philo, int flag_to_report, int status)
{
	pthread_mutex_lock(&philo->tab->print_mutex);
	if (game_over(philo->tab) == 1 && flag_to_report == 0)
	{
		pthread_mutex_unlock(&philo->tab->print_mutex);
		return ;
	}
	if (status == DIED)
		print_philo(philo, "died", 1);
	else if (status == EATING)
		print_philo(philo, "is eating", 1);
	else if (status == SLEEPING)
		print_philo(philo, "is sleeping", 1);
	else if (status == THINKING)
		print_philo(philo, "is thinking", 1);
	else if (status == TAKE_FORK_L)
		print_philo(philo, "has taken a fork (left)", 1);
	else if (status == TAKE_FORK_R)
		print_philo(philo, "has taken a fork (right)", 1);
	pthread_mutex_unlock(&philo->tab->print_mutex);
}

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
