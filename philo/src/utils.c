/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:46:40 by pvong             #+#    #+#             */
/*   Updated: 2023/03/20 15:47:59 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

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

long	convert_to_readable_time(struct timeval time)
{
	int	hms;
	int	hour;
	int	min;
	int	sec;

	hms = (time.tv_sec + SEC_PER_HOUR) % SEC_PER_DAY;
	hour = hms / SEC_PER_HOUR;
	min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	sec = hms % SEC_PER_MIN;
	printf("%d:%02d:%02d:%d\n", hour, min, sec, time.tv_usec);
	return (hms);
}