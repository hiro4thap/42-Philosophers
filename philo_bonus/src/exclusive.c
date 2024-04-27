/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclusive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:49:55 by hiono             #+#    #+#             */
/*   Updated: 2024/04/25 15:31:33 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	exclusive_set_bool(bool *dst, bool value, pthread_mutex_t *lock)
{
	if (pthread_mutex_lock(lock))
		printf("fail to lock for some reason\n");
	*dst = value;
	if (pthread_mutex_unlock(lock))
		printf("fail to unlock for some reason\n");
}

bool	exclusive_get_bool(bool *value, pthread_mutex_t *lock)
{
	bool	res;

	if (pthread_mutex_lock(lock))
		printf("fail to lock for some reason\n");
	res = *value;
	if (pthread_mutex_unlock(lock))
		printf("fail to unlock for some reason\n");
	return (res);
}

void	exclusive_set_long(long *dst, long value, pthread_mutex_t *lock)
{
	if (pthread_mutex_lock(lock))
		printf("fail to lock for some reason\n");
	*dst = value;
	if (pthread_mutex_unlock(lock))
		printf("fail to unlock for some reason\n");
}

long	exclusive_get_long(long *value, pthread_mutex_t *lock)
{
	long	res;

	if (pthread_mutex_lock(lock))
		printf("fail to lock for some reason\n");
	res = *value;
	if (pthread_mutex_unlock(lock))
		printf("fail to unlock for some reason\n");
	return (res);
}
