/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:47:06 by hiono             #+#    #+#             */
/*   Updated: 2024/04/23 18:57:34 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_table(t_table *table, int argc, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->death_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		table->max_eat_count = ft_atoi(argv[5]);
	else
		table->max_eat_count = 0;
	table->start_time = get_ms();
	table->is_finished = 0;
}

void	init_philos(t_philo *philos, t_table *table, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_eat = get_ms();
		philos[i].is_alive = 1;
		philos[i].is_full = 0;
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = &forks[(i + 1) % table->philo_num];
		philos[i].table = table;
		i++;
	}
}

void	init_forks(t_fork *forks, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		forks[i].id = i + 1;
		pthread_mutex_init(&forks[i].lock, NULL);
		i++;
	}
}
