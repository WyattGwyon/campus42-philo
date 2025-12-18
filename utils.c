/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:35:37 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:46:01 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !sim_finished(philo->table))
		printf("[%-6ld] %d has taken 1st fork"
				"\t\tno %d\n", elapsed, philo->id, philo->first_fork->fork_id);
	if (TAKE_SECOND_FORK == status && !sim_finished(philo->table))
		printf("[%-6ld] %d has taken 2nd fork"
				"\t\tno %d\n", elapsed, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !sim_finished(philo->table))
		printf("[%-6ld] %d is eating"
				"\t\t\tcnt %ld\n", elapsed, philo->id, philo->meals_eaten);
	else if (status == SLEEPING && !sim_finished(philo->table))
		printf("[%-6ld] %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !sim_finished(philo->table))
		printf("[%-6ld] %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf("[%-6ld] %d died\n", elapsed, philo->id);
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECS) - philo->table->sim_start_time;
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else 
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !sim_finished(philo->table))
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !sim_finished(philo->table))
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !sim_finished(philo->table))
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !sim_finished(philo->table))
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (status == DEAD)
			printf("%ld %d died\n", elapsed, philo->id);
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}



void	clean(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		philo = &table->philos[i];
		safe_mutex(&philo->philo_mutex, DESTROY);
		fork = &table->forks[i];
		safe_mutex(&fork->fork, DESTROY);
	}
	safe_mutex(&table->table_mutex, DESTROY);
	safe_mutex(&table->write_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}


