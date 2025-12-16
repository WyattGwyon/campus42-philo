/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	die(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;
	long	now;
	long	last_meal_time;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	now = gettime(MILLISECS);
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = now - last_meal_time;
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	think(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

void	eat(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, 
		gettime(MILLISECS));
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, *philo->table);
	if (philo->table->must_eat > 0 &&
			philo->meals_eaten == philo->table->must_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}

void	*sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	sync_thread_start(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECS));
	incr_long(&philo->table->table_mutex, &philo->table->num_running_threads);
	while (!sim_finished(philo->table))
	{
		if (philo->full)
		{
			break;
		}
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, *philo->table);
		think(philo);
	}
	return (NULL);
}


void	start_sim(t_table *table)
{
	int	i;

	i = -1;
	if (1 == table->num_of_philos)
		safe_thread(&table->philos[0].thread_id, one_philo,
				&table->philos[0], CREATE);
	else
	{
		while (++i < table->num_of_philos)
			safe_thread(&table->philos[i].thread_id, sim,
				&table->philos[i], CREATE);
	}
	safe_thread(&table->monitor, monitor_sim, table, CREATE);
	table->sim_start_time = gettime(MILLISECS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->num_of_philos)
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
}
