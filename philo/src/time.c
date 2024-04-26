/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:49:27 by hiono             #+#    #+#             */
/*   Updated: 2024/04/26 19:27:37 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// get current time in miliseconds
long	get_ms(void)
{
	struct timeval	tp;
	long			ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (ms);
}

// as original usleep surely delays
// construct the accurate one
void	ft_usleep(long ms)
{
	long	start;

	start = get_ms();
	usleep(ms * 900);
	while ((get_ms() - start) < ms)
		usleep(ms);
}

// get timestamp to print on the screen
long	get_timestamp(t_table *table)
{
	return (get_ms() - table->start_time);
}
