/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:15:57 by pvong             #+#    #+#             */
/*   Updated: 2023/04/20 12:02:16 by pvong            ###   ########.fr       */
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

# define NO_NL			0
# define NL				1

typedef struct s_th
{
	pthread_t			*th;
	int					id;
	long long			time;
	pthread_mutex_t		mutex;
}	t_th;

long convert_to_readable_time(struct timeval time);
void print_time(long int time, int flag);
long int get_time(void);

/* Utils */

void	ft_putstr_fd(char *str, int fd);
void	print_status(t_th *th, int message);
int		init_ph(t_th *threads);


#endif
