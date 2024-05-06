/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:59 by hiono             #+#    #+#             */
/*   Updated: 2024/05/06 14:52:50 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// when only one philosopher exist
// 1) take a fork
// 2) die
void	*solo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	print_action(TAKE_FORK, philo);
	return (NULL);
}

void	solo_dinner(t_philo *philos)
{
	pthread_t	monitor_td;

	protect_handle_thread(
		CREATE, &philos[0].td, solo_routine, (void *) &philos[0]);
	protect_handle_thread(CREATE, &monitor_td, monitor, (void *) philos);
	protect_handle_thread(JOIN, &philos[0].td, NULL, NULL);
	protect_handle_thread(JOIN, &monitor_td, NULL, NULL);
}

// when more than one philosopher exist
// each thread represents a philosopher looping the routine as follows
// 1) take right fork
// 2) take left fork
// 3) eat
// 4) sleep
// 5) think
// once philosopher gets full or simulation is finished, break routine
void	*multi_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
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
		philo->eat_count += 1;
		if (philo->eat_count == philo->table->max_eat_count)
		{
			philo->is_full = 1;
			//sem_post(philo->table->full);
		}
		print_action(SLEEP, philo);
		ft_usleep(philo->table->sleep_time);
		print_action(THINK, philo);
	}
	return(NULL);
}

void	wait_full(t_philo *philos, int death_pid)
{
	int	i;

	i = 0;
	while (i < philos[0].table->philo_num)
	{
		sem_wait(philos[0].table->full);
		i++;
	}
	kill(death_pid, SIGKILL);
	exit(EXIT_SUCCESS);
}

//void	wait_death(t_philo *philos)
//{

void	kill_process(t_philo *philos)
{
	int	i;

	sem_unlink("death");
	sem_unlink("full");
	sem_unlink("forks");
	sem_unlink("message");
	i = 0;
	while (i < philos[0].table->philo_num)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
}

void	multi_dinner(t_table *table, t_philo *philos)
{
	int			i;
	//pthread_t	monitor_td;
	//int			status;
	//int			full_pid;
	//int			death_pid;

	i = 0;
	while (i < table->philo_num)
	{
		philos[i].pid = fork();
		if (philos[i].pid < -1)
			exit(EXIT_FAILURE);
		if (philos[i].pid == 0)
		{
			//protect_handle_thread(CREATE, &monitor_td, monitor, (void *) &philos[i]);
			//protect_handle_thread(DETACH, &monitor_td, NULL, NULL);
			protect_handle_thread(CREATE, &philos[i].td, multi_routine, (void *) &philos[i]);
			protect_handle_thread(JOIN, &philos[i].td, NULL, NULL);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	ft_usleep(520);
	kill_process(philos);
	exit(EXIT_SUCCESS);
	//full_pid = fork();
	//death_pid = 0;
	//if (0 < full_pid)
	//	death_pid = fork();
	//if (full_pid == 0)
	//	wait_full(philos, death_pid);
	//if (death_pid == 0)
	//	exit(EXIT_SUCCESS);
	//	//wait_death(philos, full_pid);
	//waitpid(full_pid, &status, 0);
	//waitpid(death_pid, &status, 0);
	//kill_process(philos);	
	//exit(EXIT_SUCCESS);
}
