/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:14:30 by hiono             #+#    #+#             */
/*   Updated: 2024/04/26 19:28:30 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// check if all philsophers are full
static int	is_all_philos_full(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].table->philo_num)
	{
		if (!exclusive_get_bool(&philos[i].is_full, &philos[i].lock))
			return (0);
		i++;
	}
	return (1);
}

// check if any philsopher should die of starvation
static int	is_any_philo_starved(t_philo *philos)
{
	int		i;
	long	hungry_duration;

	i = 0;
	while (i < philos[0].table->philo_num)
	{
		hungry_duration = get_msecond()
			- exclusive_get_long(&philos[i].last_eat, &philos[i].lock);
		if (philos[0].table->death_time < hungry_duration)
		{
			print_action(DIE, &philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

// watch if..
// 1) all philosophers are full
// 2) any philosopher died of starvation
// then turn on "is_finished" flag
void	*monitor(void *v_philos)
{
	t_philo	*philos;

	philos = (t_philo *)v_philos;
	while (1)
	{
		if (is_all_philos_full(philos) || is_any_philo_starved(philos))
		{
			exclusive_set_bool(
				&philos[0].table->is_finished, 1, &philos[0].table->lock);
			break ;
		}
	}
	return (NULL);
}
