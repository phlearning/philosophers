/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:59:05 by pvong             #+#    #+#             */
/*   Updated: 2023/05/05 13:38:55 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	take_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->env->mutex_forks[ph->left_fork]);
	print_status(ph, TAKING_FORK);
	pthread_mutex_lock(&ph->env->mutex_forks[ph->right_fork]);
	print_status(ph, TAKING_FORK2);
}

void	clean_fork(t_ph *ph)
{
	print_status(ph, SLEEPING);
	pthread_mutex_unlock(&ph->env->mutex_forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->env->mutex_forks[ph->right_fork]);
	usleep(T2S * 1000);
	// usleep(100);
	printf("hello from sleeping \n");
}