/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:41:03 by clouden           #+#    #+#             */
/*   Updated: 2025/12/18 17:50:24 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define DEBUG_MODE 1

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef enum	e_mtx_thread
{
	CREATE,
	JOIN,
	DETACH,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
}	t_mtx_thread;

typedef enum	e_time
{
	SECONDS,
	MILLISECS,
	MICROSECS,
}	t_time;

typedef enum	e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD
}	t_philo_status;

typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct	s_philo
{
	int			id;
	long		meals_eaten;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}	t_philo;

typedef struct	s_table
{
	long		num_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		must_eat;
	long		sim_start_time;
	bool		end_sim;
	bool		all_threads_ready;
	long		num_running_threads;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

// parser.c
void	parse_input(t_table *table, int ac, char *av[]);

// untils.c
void	error_exit(char *error);
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	clean(t_table *table);

// init.c
void	init_data(t_table *table);

// safe_utils.c
void	*safe_malloc(size_t bytes);
void	mutex_error(int status, t_mtx_thread mtx_thread);
void	safe_mutex(t_mtx *mutex, t_mtx_thread mtx_thr);
void	thread_error(int status, t_mtx_thread mtx_thread);
void	safe_thread(pthread_t *thread, void *(func)(void *),
			void *data, t_mtx_thread mtx_thr);

// sim.c
bool	die(t_philo *philo);
void	think(t_philo *philo, bool start);
void	start_sim(t_table *table);

// getters_setters.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	sim_finished(t_table *table);

// sync.c
void	sync_thread_start(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long num_of_philos);
void	incr_long(t_mtx *mutex, long *value);
void	desync_philos(t_philo *philo);

// time.c
long	gettime(t_time time_code);
void	precise_usleep(long usec, t_table table);

// monitor.c
void	*monitor_sim(void *data);

// one_philo.c
void	*one_philo(void *data);

#endif
