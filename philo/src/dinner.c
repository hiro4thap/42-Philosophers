/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:59 by hiono             #+#    #+#             */
/*   Updated: 2024/04/25 17:01:48 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *v_philo)
{
	t_philo *philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 1)
		ft_usleep(30);
	while (!philo->table->is_finished && (!philo->table->max_eat_count || exclusive_get_long(&philo->eat_count, &philo->lock) < philo->table->max_eat_count))
	{
		// take fork
		if (pthread_mutex_lock(&philo->r_fork->lock))
			printf("%d fail to lock rfork for some reason\n", philo->id);
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d has taken a fork\n", get_ms() - philo->table->start_time, philo->id);
		if (pthread_mutex_lock(&philo->l_fork->lock))
			printf("%d fail to lock lfork for some reason\n", philo->id);
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
		if (pthread_mutex_unlock(&philo->l_fork->lock))
			printf("%d fail to unlock lfork for some reason\n", philo->id);
		if (pthread_mutex_unlock(&philo->r_fork->lock))
			printf("%d fail to unlock rfork for some reason\n", philo->id);
		if (exclusive_get_long(&philo->eat_count, &philo->lock) == philo->table->max_eat_count)
			exclusive_set_bool(&philo->is_full, 1, &philo->lock);
		// sleep
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d is sleeping\n", get_ms() - philo->table->start_time, philo->id);
		ft_usleep(philo->table->sleep_time);
		// think
		if (!exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
			printf("%-10ld %d is thinking\n", get_ms() - philo->table->start_time, philo->id);
		if (exclusive_get_bool(&philo->is_full, &philo->lock))
			break ;
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
		if (pthread_create(&philos[i].td, NULL, routine, (void *) &philos[i]))
			printf("fail to create philos thread\n");
		i++;
	}
	if (pthread_create(&td, NULL, monitor, (void *) philos))
		printf("fail to create monitor thread\n");
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(philos[i].td, NULL))
			printf("fail to join philos thread\n");
		i++;
	}
	if (pthread_join(td, NULL))
		printf("fail to join monitor thread\n");
}
