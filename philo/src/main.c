/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:11:33 by hiono             #+#    #+#             */
/*   Updated: 2024/04/26 19:26:42 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// 1) validate arguments
// 2) initialize structures correspoinding to the arguments
// 3) start dinner depending on the number of philosophers
// 4) free allocated memory
int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;
	t_fork	*forks;
	int		i;

	validate_args(argc, argv);
	table = init_table(argc, argv);
	forks = init_forks(&table);
	philos = init_philos(&table, forks);
	if (table.philo_num == 1)
		solo_dinner(philos);
	else if (1 < table.philo_num)
		multi_dinner(&table, philos);
	i = 0;
	while (i < table.philo_num)
		protect_handle_mutex(DESTROY, &forks[i++].lock);
	free(forks);
	free(philos);
}
