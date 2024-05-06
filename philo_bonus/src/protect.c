/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:56:24 by hiono             #+#    #+#             */
/*   Updated: 2024/05/05 17:37:19 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// error handling
// 1) print messages corresponding to the error code
// 2) then exit the program
void	handle_pthread_error(int error, t_opcode opcode)
{
	if (!error)
		return ;
	if (error == EAGAIN && opcode == CREATE)
		printf("Insufficient resources to create another thread");
	else if (error == EINVAL)
		printf("Invalid settings in attr");
	else if (error == EPERM)
		printf("No permission to set scheduling policy and parameters in attr");
	else if (error == EINVAL && opcode == JOIN)
		printf("The value specified by thread is not joinable");
	else if (error == ESRCH)
		printf("No thread found for the given thread ID.");
	else if (error == EDEADLK)
		printf("A deadlock was detected");
	exit(EXIT_FAILURE);
}

void	handle_mutex_error(int error)
{
	if (!error)
		return ;
	if (error == EAGAIN)
		printf("The maximum number of locks for mutex has been exceeded");
	else if (error == EINVAL)
		printf("The thread's priority is higher than the mutex's ceiling");
	else if (error == ENOTRECOVERABLE)
		printf("Not recoverable");
	else if (error == EOWNERDEAD)
		printf("The previous owning thread terminated while holding the lock");
	else if (error == EDEADLK)
		printf("A deadlock condition was detected");
	else if (error == EPERM)
		printf("The current thread does not own the mutex");
	exit(EXIT_FAILURE);
}

// protect functions
// 1) handles return values from malloc / pthread / mutex functions
// 2) if error is returned, pass error code to the "handle functions" above
void	*protect_malloc(size_t bytes)
{
	char	*memory;

	memory = malloc(bytes);
	if (!memory)
	{
		printf("failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	return (memory);
}

void	protect_handle_thread(
			t_opcode opcode, pthread_t *thread, void *foo(void *), void *args)
{
	int	error;

	error = 0;
	if (opcode == CREATE)
		error = pthread_create(thread, NULL, foo, args);
	else if (opcode == JOIN)
		error = pthread_join(*thread, NULL);
	else if (opcode == DETACH)
		error = pthread_detach(*thread);
	handle_pthread_error(error, opcode);
}

void	protect_handle_mutex(t_opcode opcode, pthread_mutex_t *lock)
{
	int	error;

	error = 0;
	if (opcode == INIT)
		error = pthread_mutex_init(lock, NULL);
	else if (opcode == LOCK)
		error = pthread_mutex_lock(lock);
	else if (opcode == UNLOCK)
		error = pthread_mutex_unlock(lock);
	else if (opcode == DESTROY)
		error = pthread_mutex_destroy(lock);
	handle_mutex_error(error);
}
