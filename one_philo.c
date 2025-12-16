/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	sync_thread_start(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECS));
	incr_long(&philo->table->table_mutex, &philo->table->num_running_threads);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while(!sim_finished(philo->table))
		usleep(200);
	return (NULL);
}
