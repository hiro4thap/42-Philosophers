/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:49:27 by hiono             #+#    #+#             */
/*   Updated: 2024/04/25 16:52:44 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_ms(void)
{
	struct timeval tp;

	gettimeofday(&tp, NULL);
	long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_ms();
	while((get_ms() - start) < ms)
		usleep(ms);
}

long	get_timestamp(t_table *table)
{
	return (get_ms() - table->start_time);
}
