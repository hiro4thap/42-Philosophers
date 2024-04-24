/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:11:33 by hiono             #+#    #+#             */
/*   Updated: 2024/04/23 18:57:16 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	int res;
	int	sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = 0;
	while (*str)
	{
		res += res * 10 + *str - '0';
		str++;
	}
	return (sign * res);
}

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
	init_table(&table, argc, argv);
	forks = malloc(table.philo_num * sizeof(t_fork));
	init_forks(forks, &table);
	philos = malloc(table.philo_num * sizeof(t_philo));
	init_philos(philos, &table, forks);
	//start_dinner(&table, philos, forks);
	free(forks);
	free(philos);
}
