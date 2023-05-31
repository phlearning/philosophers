/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:51:30 by pvong             #+#    #+#             */
/*   Updated: 2023/05/31 16:52:06 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	ft_isspace(char c)
// {
// 	if (c == '\t' || c == '\n' || c == '\v' ||
// 		c == '\f' || c == '\r' || c == ' ')
// 		return (1);
// 	return (0);
// }

// int	ft_isnum(char c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }

// int	ft_atoi(char *str)
// {
// 	int	res;
// 	int	sign;
// 	int	i;

// 	sign = 1;
// 	res = 0;
// 	i = 0;
// 	while (ft_isspace(str[i]))
// 		++i;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		++i;
// 	}
// 	while (str[i] && ft_isnum(str[i]))
// 	{
// 		res = res * 10 + (str[i] - '0');
// 		++i;
// 	}
// 	return (res * sign);
// }

/**
 * Will return -1 if int is greater than int_max;
 * @param str 
 * @return int 
 */
int	ft_check_max_atoi(char *str)
{
	unsigned long int nb;
	int i;

	i = 0;
	nb = 0;
	while (str[i] && ft_is_only_digit(str[i]))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}