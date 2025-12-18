/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, ac, av);
		init_data(&table);
		start_sim(&table);
		clean(&table);
	}
	else
	{
		error_exit("Invalid Input: please enter:\n"
				"./philo 5 800 200 200 [5]");
	}
	return (0);
}
