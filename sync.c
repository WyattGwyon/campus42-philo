/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_thread_start(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads, long num_of_philos)
{
	bool ret;

	ret = false;
	safe_mutex(mutex, LOCK);
	if (*threads == num_of_philos)
		ret = true;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	incr_long(t_mtx *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}

void	desync_philos(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			precise_usleep(30000, *philo->table);
		}
		else
		{
			if (philo->id % 2 == 1)
				think(philo, true);
		}
	}
}


