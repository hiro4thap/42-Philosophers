/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:14:30 by hiono             #+#    #+#             */
/*   Updated: 2024/04/25 17:01:54 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_full(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos[0].table->philo_num)
	{
		if (!exclusive_get_bool(&philos[i].is_full, &philos[i].lock))
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *v_philos)
{
	t_philo	*philos;
	int 	i;
	long	hungry_duration;

	philos = (t_philo *)v_philos;
	i = 0;
	while(1)
	{
		if (is_full(philos))
		{
			exclusive_set_bool(&philos[0].table->is_finished, 1, &philos[0].table->lock);
			break;
		}
		while (i < philos[0].table->philo_num)
		{
			hungry_duration = get_ms() - exclusive_get_long(&philos[i].last_eat, &philos[i].lock);
			if (philos[0].table->death_time < hungry_duration)
			{
				exclusive_set_bool(&philos[0].table->is_finished, 1, &philos[i].lock);
				printf("%-10ld %d died\n", get_timestamp(philos[0].table), philos[i].id);
				break;
			}
			i++;
		}
		i = 0;
		if (exclusive_get_bool(&philos[0].table->is_finished, &philos[0].table->lock))
			break ;
		ft_usleep(1);
	}
	return (NULL);
}
