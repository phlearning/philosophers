/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:26:45 by synicole          #+#    #+#             */
/*   Updated: 2023/06/01 13:56:41 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * Frees the environment structure.
 *
 * @param env The environment structure.
 *
 * @return void
 */
void	ft_free_env(t_env *env)
{
	unsigned int	i;

	if (!env)
		return ;
	if (env->philosophers != NULL)
	{
		i = 0;
		while (i < env->nb_philos)
		{
			if (env->philosophers[i] != NULL)
				free(env->philosophers[i]);
			i++;
		}
		free(env->philosophers);
	}
	free(env);
}

/**
 * Destroys the mutexes.
 *
 * @param env The environment structure.
 *
 * @return void
 */
void	ft_destroy_mutexes(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_philos)
	{
		pthread_mutex_destroy(&env->fork_locks[i]);
		pthread_mutex_destroy(&env->philosophers[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&env->write_lock);
	pthread_mutex_destroy(&env->simulation_stop_lock);
}

/**
 * Print a message with or without a detail, and return an exit code.
 *
 * @param str The string to print.
 * @param detail An optional detail to print after the string.
 * @param exit_n The integer value to return from the function.
 *
 * @return The integer exit code provided by the exit_n parameter.
*/
int	ft_msg(char *str, char *detail, int exit_n)
{
	if (!detail)
		printf("%s", str);
	else
		printf(str, detail);
	return (exit_n);
}

/**
 * Print a message and free the environment structure if it is not NULL.
 *
 * @param str The string to print.
 * @param env The environment structure.
 *
 * @return int 0
 */
int	ft_error_int(char *str, t_env *env)
{
	if (env != NULL)
		ft_free_env(env);
	printf("%s", str);
	return (0);
}

/**
 * Print a message and free the environment structure if it is not NULL.
 *
 * @param str The string to print.
 * @param env The environment structure.
 *
 * @return void* NULL
 */
void	*ft_error_null(char *str, t_env *env)
{
	if (env != NULL)
		ft_free_env(env);
	printf("%s", str);
	return (NULL);
}
