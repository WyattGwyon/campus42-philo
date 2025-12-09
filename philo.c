/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:41:14 by clouden           #+#    #+#             */
/*   Updated: 2025/12/08 11:51:06 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include "libftExt/libft.h"
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		id;
} t_fork;

typedef struct	s_philo 
{
	int		id;
	int		think_time;
	int		eat_time;
	int		sleep_time;
	int		meal_cnt;
	bool	is_full;
	bool	left_fork;
	bool	right_fork;
} t_philo;

typedef struct	s_waiter
{
	
}

void	eat(t_philo philo)
{
	pthread_mutex_lock;
	printf("philo %d is eating");
	usleep(eat_time);
	pthread_mutex_unlock;
}

void	*summon_philo(void *philo)
{
	eat(philo);
}

int	main(int ac, char *av[])
{
	t_philo	philos;
	int		philo_num;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		meal_cnt;
	int		i;

	meal_cnt = -1;
	if (ac > 6 || ac < 5)
		return (1);
	philo_num = ft_atoi(av[1]);
	die_time = ft_atoi(av[2]);
	eat_time = ft_atoi(av[3]);
	sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		times_to_eat = ft_atoi(av[5]);
	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&))

	}

	ft_atoi()
	return (0);
}
