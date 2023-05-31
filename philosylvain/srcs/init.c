/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <synicole@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:13:22 by synicole          #+#    #+#             */
/*   Updated: 2023/04/30 15:13:23 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * Assigns the forks to the philosopher.
 *
 * @param philo The philosopher to assign the forks to.
 *
 * @return void
 */
static void	ft_assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->env->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->env->nb_philos;
		philo->fork[1] = philo->id;
	}
}

/**
 * Initializes the philosophers.
 *
 * @param env The environment structure.
 *
 * @return t_philo** The array of philosophers.
 */
static t_philo	**ft_init_philosophers(t_env *env)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * env->nb_philos);
	if (!philos)
		return (ft_error_null(MSG_ERR_MALLOC, env));
	i = 0;
	while (i < env->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (ft_error_null(MSG_ERR_MALLOC, env));
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (ft_error_null(MSG_ERR_MUTEX, env));
		philos[i]->env = env;
		philos[i]->id = i;
		philos[i]->nb_meal_eaten = 0;
		ft_assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

/**
 * Initializes the forks.
 *
 * @param env The environment structure.
 *
 * @return int 1 if the forks were successfully initialized, 0 otherwise.
 */
static pthread_mutex_t	*ft_init_forks(t_env *env)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * env->nb_philos);
	if (!forks)
		return (ft_error_null(MSG_ERR_MUTEX, env));
	i = 0;
	while (i < env->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (ft_error_null(MSG_ERR_MUTEX, env));
		i++;
	}
	return (forks);
}

/**
 * Initializes the global mutexes.
 *
 * @param env The environment structure.
 *
 * @return int 1 if the mutexes were successfully initialized, 0 otherwise.
 */
static int	ft_init_global_mutexes(t_env *env)
{
	env->fork_locks = ft_init_forks(env);
	if (!env->fork_locks)
		return (0);
	if (pthread_mutex_init(&env->simulation_stop_lock, 0) != 0)
		return (ft_error_int(MSG_ERR_MUTEX, env));
	if (pthread_mutex_init(&env->write_lock, 0) != 0)
		return (ft_error_int(MSG_ERR_MUTEX, env));
	return (1);
}

/**
 * Initializes the environment structure.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 *
 * @return t_env* A pointer to the environment structure, or NULL if an error
 */
t_env	*ft_init_env(int argc, char **argv)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		return (ft_error_null(MSG_ERR_MALLOC, env));
	i = 1;
	env->nb_philos = ft_integer_atoi(argv[i++]);
	env->time_to_die = ft_integer_atoi(argv[i++]);
	env->time_to_eat = ft_integer_atoi(argv[i++]);
	env->time_to_sleep = ft_integer_atoi(argv[i++]);
	env->is_over = 0;
	env->must_eat_count = -1;
	if (argc == 6)
		env->must_eat_count = ft_integer_atoi(argv[i]);
	env->philosophers = ft_init_philosophers(env);
	if (!env->philosophers)
		return (ft_error_null(MSG_ERR_PHILO, env));
	if (!ft_init_global_mutexes(env))
		return (ft_error_null(MSG_ERR_GLOBAL_MUTEX, env));
	return (env);
}
