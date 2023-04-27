/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:59:05 by pvong             #+#    #+#             */
/*   Updated: 2023/04/27 16:10:15 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	take_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->env->mutex_forks[ph->id]);
	print_status(ph, TAKING_FORK);
	pthread_mutex_lock(&ph->env->mutex_forks[(ph->id + 1) % NB]);
	print_status(ph, TAKING_FORK2);
}

void	clean_fork(t_ph *ph)
{
	print_status(ph, SLEEPING);
	pthread_mutex_unlock(&ph->env->mutex_forks[ph->id]);
	pthread_mutex_unlock(&ph->env->mutex_forks[(ph->id + 1) % NB]);
	usleep(T2S);
}