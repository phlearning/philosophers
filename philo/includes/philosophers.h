/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:57 by pvong             #+#    #+#             */
/*   Updated: 2023/03/20 15:35:20 by pvong            ###   ########.fr       */
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

typedef struct s_philo
{
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	struct timeval	time;
}	t_philo;

/* Utils */

int		ft_isspace(char c);
int		ft_isnum(char c);
int		ft_atoi(char *str);
long	convert_to_readable_time(struct timeval time);

/* Parsing */

int		parsing(t_philo *philo, int ac, char **av);
int		parsing_2(t_philo *philo, int ac, char **av, int *err);
int		print_error(char *str);

#endif