/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:57 by pvong             #+#    #+#             */
/*   Updated: 2023/07/05 14:11:35 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/syscall.h>
# include <time.h>
# include <unistd.h>

/* -------------------------------------------------------------------------- */
/*                                   DEFINE                                   */
/* -------------------------------------------------------------------------- */

# define SEC_PER_DAY 86400
# define SEC_PER_HOUR 3600
# define SEC_PER_MIN 60

# define DIED 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define TAKE_FORK_L 4
# define TAKE_FORK_R 5

# define INPUT "./philo [nb_philo] \
[time_to_die] [time_to_eat] [time_to_sleep] \
(opt: nb_of_meals_needed)\n"

/* -------------------------------------------------------------------------- */
/*                                   STRUCT                                   */
/* -------------------------------------------------------------------------- */

typedef struct s_data	t_data;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int					id;
	int					l_fork;
	int					r_fork;
	int					meals_taken;
	long int			time_last_meal;
	long int			time_lim;
	pthread_t			th;
	pthread_mutex_t		meal_mutex;
	t_table				*tab;
}						t_philo;

typedef struct s_table
{
	unsigned int		nb_philo;
	int					game_over;
	int					meals_needed;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			start_time;
	pthread_t			monitor;
	pthread_mutex_t		stop_dining;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*fork_locks;
	t_philo				**philo;
}						t_table;

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */

/* dining.c */

void					clean_fork(t_philo *philo);
void					dining(t_data *philo, int ac);
void					eating(t_philo *philo);
int						game_over(t_table *tab);

/* dining_2.c */
void					*one_ph(t_philo *philo);
void					*ph_routine(void *data);
int						start_dining(t_table *tab);
void					take_fork(t_philo *philo);
void					thinking(t_philo *philo, int flag_print);

/* Utils.c */

int						exit_error(char *str, t_table *tab);
void					*exit_error2(char *str, t_table *tab);
void					check_n_sleep(t_table *tab, long int sleep_time);
void					end_mutexes(t_table *tab);
void					join_dining_threads(t_table *tab);

/* Atoi.c */

int						ft_isspace(char c);
int						ft_isnum(char c);
int						ft_atoi(char *str);
int						ft_check_max_atoi(char *str);

/* monitoring.c */

int						is_philo_dead(t_philo *philo);
int						check_meals_n_death(t_table *tab);
void					*monitoring(void *data);

/* Print.c */

void					ft_putstr_fd(char *str, int fd);
void					print_philo(t_philo *philo, char *str, int newline);
void					print_state(t_philo *philo, int flag_to_report,
							int status);
void					print_table(t_table *tab);

/* Time.c */

long					convert_to_readable_time(struct timeval time);
void					conv_to_read_time(long int time, int flag);
long int				get_time(void);

/* Init.c */

t_philo					**init_philo(t_table *tab);
t_table					*init_tab(int ac, char **av);
pthread_mutex_t			*init_forks(t_table *tab);
int						init_mutex(t_table *tab);

/* Parsing.c */

int						parsing(t_data *philo, int ac, char **av);
int						parsing_2(t_data *philo, int ac, char **av, int *err);
int						ft_is_only_digit(char *str);
int						is_digit(char c);
int						check_input(int ac, char **av);

/* Free.c */

void					free_tab(t_table *table);

#endif
