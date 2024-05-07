/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:11:33 by hiono             #+#    #+#             */
/*   Updated: 2024/05/07 13:12:46 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	unlink_sems(void)
{
	sem_unlink("death");
	sem_unlink("full");
	sem_unlink("forks");
	sem_unlink("message");
}

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
	dinner(&table, philos);
	unlink_sems();
	free(philos);
}
