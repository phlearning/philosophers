/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:09:18 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 13:52:34 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_tab(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	if (table)
	{
		if (table->philo)
		{
			while (table->philo[i] && i < (int) table->nb_philo)
			{
				if (table->philo[i])
				{
					free(table->philo[i]);
					table->philo[i] = NULL;
				}	
				i++;
			}
			free(table->philo);
			table->philo = NULL;
		}
	}
	free(table);
	table = NULL;
}
