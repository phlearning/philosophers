/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:57 by pvong             #+#    #+#             */
/*   Updated: 2023/04/24 14:51:19 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

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
# define DIED			4
# define OVER			5

# define NO_NL			0
# define NL				1

// TEMP
# define NB 10
# define T2T 200
# define T2E 200
# define T2S 800
# define T2D 200

struct	s_ph;

typedef struct s_th
{
	pthread_t			*th;
	struct	s_ph		*ph;
	long long			time;
	long long			start_time;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*mutex_forks;
}	t_env;

typedef struct s_ph
{
	int					id;
	int					left_fork;
	int					right_fork;
	t_env				*env;
	pthread_mutex_t		mutex_eat;
}	t_ph;

long convert_to_readable_time(struct timeval time);
void print_time(long int time, int flag);
long int get_time(void);

/* Utils */

void	ft_putstr_fd(char *str, int fd);
void	print_status(t_ph *ph, int message);
int		init_ph(t_env *threads);

#endif
