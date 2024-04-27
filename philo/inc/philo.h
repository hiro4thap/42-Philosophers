/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:58:38 by hiono             #+#    #+#             */
/*   Updated: 2024/04/27 14:36:55 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>

typedef enum e_opcode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN
}			t_opcode;

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}			t_action;

typedef struct s_fork
{
	int				id;				// fork ID
	pthread_mutex_t	lock;			// is locked when taken by a philospher
}				t_fork;

typedef struct s_table
{
	int				philo_num;		// the number of philosophers
	int				death_time;		// time to die
	int				eat_time;		// time to eat
	int				sleep_time;		// time to sleep
	long			start_time;		// time when the simulation starts
	bool			is_finished;	// is flaged on when the simulation is done
	int				max_eat_count;	// times to get full, where 0 means infinite
	pthread_mutex_t	lock;			// is locked when read / written by thread
}			t_table;

typedef struct s_philo
{
	int				id;				// philospher's ID
	long			eat_count;		// how many times they've eaten
	long			last_eat;		// last time they ate
	bool			is_full;		// flag representing if they are full
	t_fork			*r_fork;		// is used to lock fork while eating
	t_fork			*l_fork;		// is used to lock fork while eating
	pthread_t		td;				// thread ID, passed to create / join thread
	t_table			*table;			// is used to refer to the params in table
	pthread_mutex_t	lock;			// is locked when read / written by thread
}			t_philo;

void	validate_args(int argc, char **argv);
t_table	init_table(int argc, char **argv);
t_philo	*init_philos(t_table *table, t_fork *forks);
t_fork	*init_forks(t_table *table);
void	*protect_malloc(size_t bytes);
void	protect_handle_thread(
			t_opcode opcode, pthread_t *thread, void *foo(void *), void *args);
void	protect_handle_mutex(t_opcode opcode, pthread_mutex_t *lock);
long	get_msecond(void);
void	ft_usleep(long ms);
long	get_timestamp(t_table *table);
int		ft_atoi(char *str);
void	print_action(t_action action, t_philo *philo);
void	solo_dinner(t_philo *philos);
void	multi_dinner(t_table *table, t_philo *philos);
void	*monitor(void *v_philos);
void	exclusive_set_bool(bool *dst, bool value, pthread_mutex_t *lock);
bool	exclusive_get_bool(bool *value, pthread_mutex_t *lock);
void	exclusive_set_long(long *dst, long value, pthread_mutex_t *lock);
long	exclusive_get_long(long *value, pthread_mutex_t *lock);

#endif
