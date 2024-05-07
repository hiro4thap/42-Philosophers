/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:59 by hiono             #+#    #+#             */
/*   Updated: 2024/05/07 13:30:29 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// 1) kill all processes in case anyone stays alive
void	kill_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].table->philo_num)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
}

// each thread represents a philosopher looping the routine as follows
// 1) take right fork (sem wait)
// 2) take left fork (sem wait)
// 3) eat (sem post)
// 4) sleep
// 5) think
// once philosopher gets full or simulation is finished, break routine
void	routine(t_philo *philo)
{
	while (!philo->is_full)
	{
		sem_wait(philo->table->forks);
		print_action(TAKE_FORK, philo);
		sem_wait(philo->table->forks);
		print_action(TAKE_FORK, philo);
		print_action(EAT, philo);
		ft_usleep(philo->table->eat_time);
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		exclusive_set_long(&philo->last_eat, get_msecond(), &philo->lock);
		philo->eat_count += 1;
		if (philo->eat_count == philo->table->max_eat_count)
		{
			philo->is_full = 1;
			sem_post(philo->table->full);
		}
		print_action(SLEEP, philo);
		ft_usleep(philo->table->sleep_time);
		print_action(THINK, philo);
	}
}

// 1) fork() to create as many processes as philosophers
// 2) each process monitors if a philosopher is alive as well
// 3) main process monitors any dead or all full
void	dinner(t_table *table, t_philo *philos)
{
	int			i;
	pthread_t	monitor_td;

	i = 0;
	while (i < table->philo_num)
	{
		philos[i].pid = fork();
		if (philos[i].pid < -1)
			exit(EXIT_FAILURE);
		if (philos[i].pid == 0)
		{
			protect_handle_thread(CREATE,
				&monitor_td, monitor, (void *) &philos[i]);
			protect_handle_thread(DETACH, &monitor_td, NULL, NULL);
			routine(&philos[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	monitor_philos(philos);
	kill_philos(philos);
}
