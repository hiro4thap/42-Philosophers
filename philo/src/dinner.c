/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:59 by hiono             #+#    #+#             */
/*   Updated: 2024/04/26 19:22:06 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// when only one philosopher exist
// 1) take a fork
// 2) die
void	*solo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	print_action(TAKE_FORK, philo);
	return (NULL);
}

void	solo_dinner(t_philo *philos)
{
	pthread_t	monitor_td;

	protect_handle_thread(
		CREATE, &philos[0].td, solo_routine, (void *) &philos[0]);
	protect_handle_thread(CREATE, &monitor_td, monitor, (void *) philos);
	protect_handle_thread(JOIN, &philos[0].td, NULL, NULL);
	protect_handle_thread(JOIN, &monitor_td, NULL, NULL);
}

// when more than one philosopher exist
// each thread represents a philosopher looping the routine as follows
// 1) take right fork
// 2) take left fork
// 3) eat
// 4) sleep
// 5) think
// once philosopher gets full or simulation is finished, break routine
void	eat(t_philo *philo)
{
	if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
	{
		exclusive_set_long(&philo->last_eat, get_ms(), &philo->lock);
		print_action(EAT, philo);
	}
	ft_usleep(philo->table->eat_time);
	exclusive_set_long(&philo->eat_count, philo->eat_count + 1, &philo->lock);
	if (exclusive_get_long(
			&philo->eat_count, &philo->lock) == philo->table->max_eat_count)
		exclusive_set_bool(&philo->is_full, 1, &philo->lock);
}

void	*multi_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->id % 2 == 1)
		ft_usleep(20);
	while (!philo->table->is_finished)
	{
		protect_handle_mutex(LOCK, &philo->r_fork->lock);
		print_action(TAKE_FORK, philo);
		protect_handle_mutex(LOCK, &philo->l_fork->lock);
		print_action(TAKE_FORK, philo);
		eat(philo);
		protect_handle_mutex(UNLOCK, &philo->l_fork->lock);
		protect_handle_mutex(UNLOCK, &philo->r_fork->lock);
		print_action(SLEEP, philo);
		ft_usleep(philo->table->sleep_time);
		print_action(THINK, philo);
		if (exclusive_get_bool(&philo->is_full, &philo->lock))
			break ;
	}
	return (NULL);
}

void	multi_dinner(t_table *table, t_philo *philos)
{
	int			i;
	pthread_t	monitor_td;

	i = 0;
	while (i < table->philo_num)
	{
		protect_handle_thread(
			CREATE, &philos[i].td, multi_routine, (void *) &philos[i]);
		i++;
	}
	protect_handle_thread(CREATE, &monitor_td, monitor, (void *) philos);
	i = 0;
	while (i < table->philo_num)
	{
		protect_handle_thread(JOIN, &philos[i].td, NULL, NULL);
		i++;
	}
	protect_handle_thread(JOIN, &monitor_td, NULL, NULL);
}
