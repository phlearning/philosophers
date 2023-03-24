/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:09:18 by pvong             #+#    #+#             */
/*   Updated: 2023/03/24 14:09:22 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_tab(t_table *table)
{
	int i;

	i = 0;
	if (table)
	{
		if (table->philo)
		{
			while (table->philo[i])
			{
				free(table->philo[i]);
				i++;
			}
			free(table->philo);
		}
		if (table->data)
			free(table->data);
	}
}
