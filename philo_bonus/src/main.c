/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:11:33 by hiono             #+#    #+#             */
/*   Updated: 2024/05/05 19:02:23 by hiono            ###   ########.fr       */
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

	validate_args(argc, argv);
	table = init_table(argc, argv);
	philos = init_philos(&table);
	init_semaphores(&table);
	if (table.philo_num == 1)
		solo_dinner(philos);
	else if (1 < table.philo_num)
		multi_dinner(&table, philos);
	free(philos);
}
