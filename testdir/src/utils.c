/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:09:00 by pvong             #+#    #+#             */
/*   Updated: 2023/05/01 16:38:50 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

void	print_status(t_ph *ph, int message)
{
	pthread_mutex_lock(&ph->env->mutex_print);
	ph->env->time = get_time() - ph->env->start_time;
	print_time(ph->env->time, NO_NL);
	printf("Philosopher %d ", ph->id + 1);
	if (message == TAKING_FORK)
		printf("has taken a fork %d\n", ph->left_fork + 1);
	else if (message == TAKING_FORK2)
		printf("has taken a fork %d\n", ph->right_fork + 1);
	else if (message == EATING)
		printf("is eating\n");
	else if (message == SLEEPING)
		printf("is sleeping\n");
	else if (message == THINKING)
		printf("is thinking\n");
	else if (message == DIED)
		printf("died\n");
	pthread_mutex_unlock(&ph->env->mutex_print);
}