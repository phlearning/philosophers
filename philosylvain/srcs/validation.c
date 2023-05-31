/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:09:48 by synicole          #+#    #+#             */
/*   Updated: 2023/05/31 16:35:11 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * Check if a string contains only digits.
 *
 * @param str The string to check.
 *
 * @return int 1 if the string contains only digits, otherwise 0.
 */
static int	ft_contains_only_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Convert a string to an integer.
 *
 * @param str The string to convert.
 *
 * @return int The integer value of the string, or -1 if the value is too big.
 */
int	ft_integer_atoi(const char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/**
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 *
 * @return int 1 if all arguments are valid, otherwise 0.
 */
int	check_input(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (!ft_contains_only_digit(argv[i]))
			return (ft_msg(MSG_INVALID_INPUT_DIGIT, argv[i], 0));
		nb = ft_integer_atoi(argv[i]);
		// printf("nb : %d\n", nb);
		if (nb == -1)
			return (ft_msg(MSG_INVALID_INPUT_DIGIT, argv[i], 0));
		if (i == 1 && (nb <= 0 || nb > ft_integer_atoi(MAX_PHILOS)))
			return (ft_msg(MSG_INVALID_INPUT_PHILO, MAX_PHILOS, 0));
		i++;
	}
	return (1);
}
