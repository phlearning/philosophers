/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:09:18 by pvong             #+#    #+#             */
/*   Updated: 2023/05/31 17:18:04 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_tab(t_table *table)
{
	int i;

	i = 0;
	if (!table)
		return ;
	if (table)
	{
		if (table->philo)
		{
			while (table->philo[i])
			{
				if (table->philo[i])
					free(table->philo[i]);
				i++;
			}
			free(table->philo);
		}
		// if (table->data)
		// 	free(table->data);
	}
	free(table);
}
