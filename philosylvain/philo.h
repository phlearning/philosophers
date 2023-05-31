/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <synicole@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:43:07 by synicole          #+#    #+#             */
/*   Updated: 2023/04/14 19:43:09 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// ----- DEBUG MODE ----- //
# define DEBUG 0

// ----- MAX ----- //
# define MAX_PHILOS	"250"

// ----- MESSAGES ----- //
# define MSG_USAGE "Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define MSG_INVALID_INPUT_DIGIT "%s must be a valid integer between 0 \
and 2147483647.\n"
# define MSG_INVALID_INPUT_PHILO "Must be between 1 and %s philosophers.\n"
# define MSG_ERR_MALLOC	"Could not allocate memory.\n"
# define MSG_ERR_MUTEX	"Could not create mutex.\n"
# define MSG_ERR_THREAD	"Could not create thread.\n"
# define MSG_ERR_PHILO	"Could not create philosopher.\n"
# define MSG_ERR_GLOBAL_MUTEX "Could not create global mutex.\n"

// ----- STRUCTURES ----- //
typedef struct s_env	t_env;
typedef struct s_philo	t_philo;

typedef struct s_env
{
	int				must_eat_count;
	unsigned int	nb_philos;
	unsigned int	is_over;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	t_philo			**philosophers;
	pthread_t		monitoring;
	pthread_mutex_t	simulation_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
}	t_env;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	nb_meal_eaten;
	unsigned int	fork[2];
	time_t			last_meal;
	t_env			*env;
	pthread_t		thread;
	pthread_mutex_t	meal_time_lock;
}	t_philo;

// ----- ENUM ----- //
typedef enum e_status
{
	E_DIED = 0,
	E_EATING = 1,
	E_SLEEPING = 2,
	E_THINKING = 3,
	E_GOT_FORK_1 = 4,
	E_GOT_FORK_2 = 5
}	t_status;

// ----- ENV ----- //
t_env	*ft_init_env(int argc, char **argv);

// ----- VALIDATION ----- //
int		ft_is_valid_input(int argc, char **argv);
int		ft_integer_atoi(const char *str);

// ----- SIMULATION ----- //
int		ft_start_simulation(t_env *env);
void	ft_stop_simulation(t_env *env);
void	ft_simulation_start_delay(time_t start_time);
int		ft_is_simulation_over(t_env *env);

// ----- PHILOSOPHER ----- //
void	*ft_philo_routine(void *data);

// ----- MONITORING ----- //
void	*ft_monitoring(void *data);

// ----- TIME ----- //
time_t	ft_get_time_in_ms(void);

// ----- OUTPUT ----- //
void	ft_write_status(t_philo *philo, int monitoring_report, t_status status);

// ----- EXIT ----- //
int		ft_msg(char *str, char *detail, int exit_n);
void	*ft_error_null(char *str, t_env *env);
int		ft_error_int(char *str, t_env *env);
void	ft_free_env(t_env *env);
void	ft_destroy_mutexes(t_env *env);

// ----- DEBUG ----- //
void	ft_write_status_debug(t_philo *philo, t_status status);
void	ft_write_outcome_debug(t_env *env);

#endif