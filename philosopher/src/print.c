/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:09:05 by pvong             #+#    #+#             */
/*   Updated: 2023/06/06 11:46:06 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	print_philo_infos(t_table *tab)
{
	unsigned int	i;

	i = -1;
	if (!tab)
		return ;
	printf("\n------ INFO PHILO -------\n\n");
	while (tab->philo[++i])
	{
		printf("--- PHILO_%d ---\n", tab->philo[i]->id);
		printf("Left_fork: \t%d\n", tab->philo[i]->l_fork);
		printf("Left_fork: \t%d\n", tab->philo[i]->r_fork);
		printf("\n");
	}
}