/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:09:00 by pvong             #+#    #+#             */
/*   Updated: 2023/04/20 15:45:53 by pvong            ###   ########.fr       */
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

void	print_status(t_th *th, int message, int i)
{
	th->time = get_time() - th->start_time;
	print_time(th->time, NO_NL);
	printf(" Philosopher %d ", i);
	if (message == TAKING_FORK)
		printf("has taken a fork\n");
	if (message == EATING)
		printf("is eating\n");
	if (message == SLEEPING)
		printf("sleeping\n");
	if (message == THINKING)
		printf("is thinking\n");
}