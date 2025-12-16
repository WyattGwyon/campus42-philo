/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_sim(void *data)
{
	t_table	*table;
	int		i;
	
	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->num_running_threads, &table->num_of_philos))
		;
	while (!sim_finished(table))
	{
		i = -1;
		while (++i < table->num_of_philos && !sim_finished(table))
		{
			if (die(&table->philos[i]))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				write_status(DEAD, &table->philos[i], DEBUG_MODE);
			}
		}
	}
	
	return (NULL);
}
