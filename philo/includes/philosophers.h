/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:57 by pvong             #+#    #+#             */
/*   Updated: 2023/03/20 17:16:17 by pvong            ###   ########.fr       */
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
# include <semaphore.h>

# define SEC_PER_DAY   86400
# define SEC_PER_HOUR  3600
# define SEC_PER_MIN   60

typedef struct s_data
{
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	struct timeval	time;
	t_philo			
}	t_data;

typedef	struct s_philo
{
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_think;
	pthread_mutex_t	mutex_sleep;
	int				id;
}	t_philo;

/* Utils */

int		ft_isspace(char c);
int		ft_isnum(char c);
int		ft_atoi(char *str);
long	convert_to_readable_time(struct timeval time);

/* Parsing */

int		parsing(t_data *philo, int ac, char **av);
int		parsing_2(t_data *philo, int ac, char **av, int *err);
int		print_error(char *str);

void	dining(t_data *philo, int ac);

#endif