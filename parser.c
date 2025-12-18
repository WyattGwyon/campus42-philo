/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:35:37 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:46:01 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_isalldigit(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (0);
		i++;
	}
	return (1);
}

__int128_t	ft_atol(const char *str)
{
	int			sign;
	__int128_t	num;

	sign = 1;
	num = 0;
	if (*str == '\0')
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

int	is_valid_range(t_table *table)
{
	if ((table->num_of_philos < 1 || table->num_of_philos > INT_MAX) || \
		(table->time_to_die < 1 || table->time_to_die > INT_MAX) || \
		(table->time_to_eat < 1 || table->time_to_eat > INT_MAX) || \
		(table->time_to_sleep < 1 || table->time_to_sleep > INT_MAX) || \
		(table->must_eat < 0 || table->must_eat > INT_MAX))
		return (0);
	return (1);
}

void parse_input(t_table *table, int ac, char *av[])
{
	if (!ft_isalldigit(av[1]) || !ft_isalldigit(av[2]) || \
		!ft_isalldigit(av[3])  || !ft_isalldigit(av[4]) || \
		(ac == 6 && !ft_isalldigit(av[5])))
		error_exit("Invalid input: please enter only numerical args");
	table->num_of_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	table->must_eat = 0;
	if (ac == 6)
	{
		table->must_eat = ft_atol(av[5]);
		if (!is_valid_range(table))
			error_exit("Invalid input: please do not enter less than 1"
				"or exceed INT_MAX");
	}
	else
	{
		if (!is_valid_range(table))
			error_exit("Invalid input: please do not enter less than 1"
				"or exceed INT_MAX");
		table->must_eat = -1;
	}
}
