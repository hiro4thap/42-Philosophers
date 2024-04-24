/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:14:30 by hiono             #+#    #+#             */
/*   Updated: 2024/04/24 13:15:29 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_full(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos[0].table->philo_num)
	{
		if (!philos[i].is_full)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *v_philos)
{
	t_philo	*philos = (t_philo *)v_philos;
	int i = 0;
	while(1)
	{
		if (is_full(philos))
		{
			philos[0].table->is_finished = 1;
			break;
		}
		while (i < philos[0].table->philo_num)
		{
			if (philos[0].table->death_time < get_ms() - philos[i].last_eat)
			{
				philos[i].is_alive = 0;
				philos[0].table->is_finished = 1;
				printf("%-10ld %d eat_count: %d, passed_time: %ld\n", get_ms() - philos[i].last_eat, philos[i].id, philos[i].eat_count, get_ms() - philos[i].last_eat);
				printf("%-10ld %d died\n", get_ms() - philos[i].last_eat, philos[i].id);
				break;
			}
			i++;
		}
		i = 0;
		if (philos[0].table->is_finished)
			break ;
		ft_usleep(1);
	}
	return (NULL);
}


