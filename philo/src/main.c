/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:11:33 by hiono             #+#    #+#             */
/*   Updated: 2024/04/24 13:12:14 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;
	t_fork	*forks;

	if (!(argc == 5 || argc == 6))
	{
		printf("The number of arguments should be 4 or 5\n");
		return (1);
	}
	if (!is_args_pnum(argc, argv))
	{
		printf("All arguments should be positive numbers");
		return (1);
	}
	table = init_table(argc, argv);
	forks = init_forks(&table);
	philos = init_philos(&table, forks);
	start_dinner(&table, philos);
	int i = 0;
	while (i < table.philo_num)
	{
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	free(forks);
	free(philos);
}
