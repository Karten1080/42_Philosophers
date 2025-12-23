/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:53:18 by asmati            #+#    #+#             */
/*   Updated: 2025/12/23 16:53:18 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error With the Malloc");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && ((LOCK == opcode) || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread blocked"
			"waiting for mutex");
	else if (EPERM == status)
		error_exit("The caller does not have the privilege to"
			"perform the operation.");
	else if (ENOMEM == status)
		error_exit("Insufficient memory exists to initialize the mutex.");
	else if (EBUSY == status)
		error_exit("The mutex could not be acquired because"
			"it was already locked.");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("Insufficient resources to  create  another thread.");
	else if (EPERM == status)
		error_exit("No permission to set the scheduling policy"
			"and parameters specified in attr.");
	else if (EINVAL == status && (CREATE == opcode))
		error_exit("Invalid settings in attr.");
	else if (EINVAL == status && (DETACH == opcode || JOIN == opcode))
		error_exit("thread is not a joinable thread.");
	else if (ESRCH == status)
		error_exit("No thread with  the  ID  thread  could  be found.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected (e.g.,"
			"two threads tried to join with each"
			"other); or thread specifies the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, void *(*start_routine)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, start_routine, data),
			opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle"
			"Use CREATE JOIN OR DETACH");
}
