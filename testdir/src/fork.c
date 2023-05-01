/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:59:05 by pvong             #+#    #+#             */
/*   Updated: 2023/05/01 17:54:41 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	take_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->env->mutex_forks[ph->left_fork]);
	print_status(ph, TAKING_FORK);
	printf("\t left_fork: %d\n", ph->left_fork + 1);
	pthread_mutex_lock(&ph->env->mutex_forks[ph->right_fork]);
	print_status(ph, TAKING_FORK2);
	printf("\t right_fork: %d\n", ph->right_fork + 1);
}

void	clean_fork(t_ph *ph)
{
	print_status(ph, SLEEPING);
	pthread_mutex_unlock(&ph->env->mutex_forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->env->mutex_forks[ph->right_fork]);
	usleep(T2S * 1000);
}