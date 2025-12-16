/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:47 by clouden           #+#    #+#             */
/*   Updated: 2025/12/10 19:49:20 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*mem;

	mem = calloc(bytes, sizeof(char));
	if (mem == NULL)
		error_exit("Malloc Error");
	return (mem);
}

void	mutex_error(int status, t_mtx_thread mtx_thread)
{
	if (status == 0)
		return ;
	if (status == EINVAL && mtx_thread == INIT)
		error_exit("Invalid mutex argument.");
	else if (status == EINVAL && (mtx_thread == LOCK || mtx_thread == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EDEADLK)
		error_exit("Resource deadlock for mutex avoided.");
	else if (status == EPERM)
		error_exit("The current thread does not hld a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("Process cannot allocate memory to create a mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked.");
}

void	safe_mutex(t_mtx *mutex, t_mtx_thread mtx_thr)
{
	if (mtx_thr == INIT)
	{
		int status = pthread_mutex_init(mutex, NULL);
		mutex_error(status, mtx_thr);
	}
	else if (mtx_thr == LOCK)
		mutex_error(pthread_mutex_lock(mutex), mtx_thr);
	else if (mtx_thr == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), mtx_thr);
	else if (mtx_thr == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), mtx_thr);
	else
		error_exit("Wrong mtx_thread code for mutex.");
}

void	thread_error(int status, t_mtx_thread mtx_thread)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread.");
	else if (status == EPERM)
		error_exit("The caller does not have permission for thread.");
	else if (status == EINVAL && mtx_thread == CREATE)
		error_exit("Invalid attribute for thread.");
	else if (status == EINVAL && (mtx_thread == JOIN || mtx_thread == DETACH))
		error_exit("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		error_exit("No thread with specified ID found.");
	else if (status == EDEADLK)
		error_exit("Deadlock detected for thread.");
}

void	safe_thread(pthread_t *thread, void *(func)(void *),
		void *data, t_mtx_thread mtx_thr)
{
	if (mtx_thr == CREATE)
		thread_error(pthread_create(thread, NULL, func, data), mtx_thr);
	else if (mtx_thr == JOIN)
		thread_error(pthread_join(*thread, NULL), mtx_thr);
	else if (mtx_thr == DETACH)
		thread_error(pthread_detach(*thread), mtx_thr);
	else
		error_exit("Wrong mtx_thread code for thread.");
}
