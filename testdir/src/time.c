/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:42:25 by pvong             #+#    #+#             */
/*   Updated: 2023/05/01 17:12:36 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

long convert_to_readable_time(struct timeval time)
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

void print_time(long int time, int flag)
{
	long int	h;
	long int	m;
	long int	s;
	long int	ms;

	h = time / 1000;
	h = h % SEC_PER_DAY;
	m = (h % SEC_PER_HOUR) / SEC_PER_MIN;
	s = h % SEC_PER_MIN;
	ms = time % 1000;
	h /= SEC_PER_HOUR;
	printf("%02ldh%02ldm%02lds%03ldms\t", h, m, s, ms);
	if (flag == 1)
		printf("\n");
}

long int get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec + 2 * SEC_PER_HOUR ) * 1000 \
			+ current_time.tv_usec / 1000);
}
