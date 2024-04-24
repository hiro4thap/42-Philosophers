/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:59 by hiono             #+#    #+#             */
/*   Updated: 2024/04/24 18:24:20 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *v_philo)
{
	t_philo *philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 1)
		ft_usleep(40);
	//while (!philo->table->is_finished && (!philo->table->max_eat_count || exclusive_get_long(&philo->eat_count, &philo->lock) < philo->table->max_eat_count))
	while (!philo->table->is_finished)
	{
		// take fork
		pthread_mutex_lock(&philo->r_fork->lock);
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d has taken a fork\n", get_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(&philo->l_fork->lock);
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d has taken a fork\n", get_ms() - philo->table->start_time, philo->id);
		// eat
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
		{
			exclusive_set_long(&philo->last_eat, get_ms(), &philo->lock);
			printf("%-10ld %d is eating\n", get_ms() - philo->table->start_time, philo->id);
		}
		ft_usleep(philo->table->eat_time);
		exclusive_set_long(&philo->eat_count, philo->eat_count + 1, &philo->lock);
		pthread_mutex_unlock(&philo->l_fork->lock);
		pthread_mutex_unlock(&philo->r_fork->lock);
		if (exclusive_get_long(&philo->eat_count, &philo->lock) == philo->table->max_eat_count)
		{
			exclusive_set_bool(&philo->is_full, 1, &philo->lock);
			break;
		}
		// sleep
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d is sleeping\n", get_ms() - philo->table->start_time, philo->id);
		ft_usleep(philo->table->sleep_time);
		// think
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d is thinking\n", get_ms() - philo->table->start_time, philo->id);
	}
	return (NULL);
}

void	start_dinner(t_table *table, t_philo *philos)
{
	int			i;
	pthread_t	td;

	i = 0;
	ft_usleep(10); //for debug
	while (i < table->philo_num)
	{
		pthread_create(&philos[i].td, NULL, routine, (void *) &philos[i]);
		i++;
	}
	pthread_create(&td, NULL, monitor, (void *) philos);
	i = 0;
	while (i < table->philo_num)
	{
		pthread_join(philos[i].td, NULL);
		i++;
	}
	pthread_join(td, NULL);
}
