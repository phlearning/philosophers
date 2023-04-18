/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:57 by pvong             #+#    #+#             */
/*   Updated: 2023/04/18 11:43:24 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

# define SEC_PER_DAY    86400
# define SEC_PER_HOUR    3600
# define SEC_PER_MIN    60

# define TAKING_FORK    0
# define EATING         1
# define SLEEPING       2
# define THINKING       3

typedef struct s_data
{
	int					nb_philo;
	int					nb_forks;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals;
	long int			time_start;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					state;
	int					l_fork;
	int					r_fork;
	int					meals_taken;
	long int			time_lim;
	pthread_t			th;
}	t_philo;

typedef struct s_table
{
	t_data				*data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death;
	t_philo				**philo;
}	t_table;

/* Eating */

void			dining(t_data *philo, int ac);
void			*eating(void *arg);

/* Fork */

/** Utils **/
/* Atoi */

int				ft_isspace(char c);
int				ft_isnum(char c);
int				ft_atoi(char *str);

/* Print */

int				print_error(char *str);
void			print_table(t_data *philo);
void			print_message(t_philo *philo, t_table *tab, int message);
void			ft_putstr_fd(char *str, int fd);

/* Time */

long			convert_to_readable_time(struct timeval time);
void			conv_to_read_time(long int time, int flag);
long int		get_time(void);

int				exit_error(char *str, t_table *tab);

/* Init */

int				init(int ac, char **av, t_table *tab);

/* Parsing */

int				parsing(t_data *philo, int ac, char **av);
int				parsing_2(t_data *philo, int ac, char **av, int *err);
int				init_philo(t_table *tab);

/* Free */

void			free_tab(t_table *table);


#endif
