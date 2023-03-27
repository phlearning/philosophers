/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:46:40 by pvong             #+#    #+#             */
/*   Updated: 2023/03/22 10:14:36 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
    c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_atoi(char *str)
{
	int res;
	int sign;
	int i;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (str[i] && ft_isnum(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	return (res * sign);
}

long convert_to_readable_time(struct timeval time)
{
	int hms;
	int hour;
	int min;
	int sec;

	hms = (time.tv_sec + SEC_PER_HOUR) % SEC_PER_DAY;
	hour = hms / SEC_PER_HOUR;
	min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	sec = hms % SEC_PER_MIN;
	printf("%d:%02d:%02d:%d\n", hour, min, sec, time.tv_usec);
	return (hms);
}

void conv_to_read_time(long int time, int flag)
{
	long int h;
	long int m;
	long int s;
	long int ms;

	h = time / 1000;
	h = (h + SEC_PER_HOUR) % SEC_PER_DAY;
	m = (h % SEC_PER_HOUR) / SEC_PER_MIN;
	s = h % SEC_PER_MIN;
	ms = time % 1000;
	h /= SEC_PER_HOUR;
	printf("%ldh%02ldm%02lds%03ldms", h, m, s, ms);
	if (flag == 1)
		printf("\n");
}

long int get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void print_table(t_data *philo)
{
	printf("---------- TABLE ----------\n");
	printf("nb of philo: %d\n", philo->nb_philo);
	printf("death timer: %dms\n", philo->time_to_die);
	printf("eat time: %dms\n", philo->time_to_eat);
	printf("sleep time: %dms\n", philo->time_to_sleep);
	if (philo->nb_of_meals > 0)
		printf("nb_of_meals: %d\n", philo->nb_of_meals);
	printf("time_start: ");
	conv_to_read_time(philo->time_start, 1);
	printf("---------- ----- ----------\n");
}

void print_message(t_philo *philo, t_table *tab, int message)
{
	long int time;

	time = get_time() - tab->data->time_start;
	conv_to_read_time(time, 0);
	printf("%d ", philo->id);
	if (message == TAKING_FORK)
		printf("has taken a fork\n");
	if (message == EATING)
		printf("is eating\n");
	if (message == SLEEPING)
		printf("is sleeping\n");
	if (message == THINKING)
		printf("is thinking\n");
}