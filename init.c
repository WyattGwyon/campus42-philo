/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	num_of_philos;

	num_of_philos = philo->table->num_of_philos;
	if (philo_pos % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % num_of_philos];
	}
	else 
	{
		philo->second_fork = &forks[philo_pos];
		philo->first_fork = &forks[(philo_pos + 1) % num_of_philos];
	}
}
*/

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	num_of_philos;

	num_of_philos = philo->table->num_of_philos;
	philo->first_fork = &forks[(philo_pos + 1) % num_of_philos];
	philo->second_fork = &forks[philo_pos];
	if (philo_pos % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % num_of_philos];
	}
}

void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_of_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->full = false;
		philo->table = table;
		philo->last_meal_time = 0;
		safe_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->num_running_threads = 0;
	safe_mutex(&table->table_mutex, INIT);
	safe_mutex(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->num_of_philos);
	table->philos = safe_malloc(sizeof(t_philo) * table->num_of_philos);
	while (++i < table->num_of_philos)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	init_philo(table);
}
