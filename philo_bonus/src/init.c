/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:47:06 by hiono             #+#    #+#             */
/*   Updated: 2024/05/06 14:47:52 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_table	init_table(int argc, char **argv)
{
	t_table	table;

	table.philo_num = ft_atoi(argv[1]);
	table.death_time = ft_atoi(argv[2]);
	table.eat_time = ft_atoi(argv[3]);
	table.sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		table.max_eat_count = ft_atoi(argv[5]);
	else
		table.max_eat_count = 0;
	table.start_time = get_msecond();
	table.is_finished = 0;
	pthread_mutex_init(&table.lock, NULL);
	return (table);
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = protect_malloc(table->philo_num * sizeof(t_philo));
	i = 0;
	while (i < table->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_eat = get_msecond();
		philos[i].is_full = 0;
		philos[i].table = table;
		pthread_mutex_init(&philos[i].lock, NULL);
		i++;
	}
	return (philos);
}

void	init_semaphores(t_table *table)
{
	sem_unlink("death");
	sem_unlink("full");
	sem_unlink("forks");
	sem_unlink("message");
	table->death = sem_open("death", O_CREAT, 0600, 0);
	table->full = sem_open("full", O_CREAT, 0600, 0);
	table->forks = sem_open("forks", O_CREAT, 0600, table->philo_num);
	table->message = sem_open("message", O_CREAT, 0600, 1);
}
