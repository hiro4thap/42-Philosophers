/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:59 by hiono             #+#    #+#             */
/*   Updated: 2024/04/24 13:16:00 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *v_philo)
{
	t_philo *philo = (t_philo *)v_philo;
	if (philo->id % 2 == 1)
		ft_usleep(40);
	while (!philo->table->is_finished && (!philo->table->max_eat_count || philo->eat_count < philo->table->max_eat_count))
	{
		// take fork
		pthread_mutex_lock(&philo->r_fork->lock);
		if (!philo->table->is_finished)
			printf("%-10ld %d has taken a fork\n", get_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(&philo->l_fork->lock);
		if (!philo->table->is_finished)
			printf("%-10ld %d has taken a fork\n", get_ms() - philo->table->start_time, philo->id);
		// eat
		if (!philo->table->is_finished)
		{
			philo->last_eat = get_ms();
			printf("%-10ld %d is eating\n", get_ms() - philo->table->start_time, philo->id);
		}
		ft_usleep(philo->table->eat_time);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->l_fork->lock);
		pthread_mutex_unlock(&philo->r_fork->lock);
		if (philo->eat_count == philo->table->max_eat_count)
		{
			philo->is_full = 1;
			break;
		}
		// sleep
		if (!philo->table->is_finished)
			printf("%-10ld %d is sleeping\n", get_ms() - philo->table->start_time, philo->id);
		ft_usleep(philo->table->sleep_time);
	}
	return (NULL);
}

void	start_dinner(t_table *table, t_philo *philos)
{
	int			i;
	pthread_t	td;

	i = 0;
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
