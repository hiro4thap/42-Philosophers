/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:14:30 by hiono             #+#    #+#             */
/*   Updated: 2024/05/05 19:01:24 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// check if any philsopher should die of starvation
static int	is_philo_starved(t_philo *philo)
{
	long	hungry_duration;

	hungry_duration = get_msecond()
		- exclusive_get_long(&philo->last_eat, &philo->lock);
	if (philo->table->death_time < hungry_duration)
	{
		print_action(DIE, philo);
		return (1);
	}
	return (0);
}

// watch if..
// 1) all philosophers are full
// 2) any philosopher died of starvation
// then turn on "is_finished" flag
void	*monitor(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (1)
	{
		if (is_philo_starved(philo))
		{
			sem_post(philo->table->death);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
