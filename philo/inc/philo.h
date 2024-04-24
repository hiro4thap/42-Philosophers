/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:58:38 by hiono             #+#    #+#             */
/*   Updated: 2024/04/24 13:15:51 by hiono            ###   ########.fr       */
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

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_table
{
	int		philo_num;
	int		death_time;
	int		eat_time;
	int		sleep_time;
	long	start_time;
	int		is_finished; //someone dead or all full
	int		max_eat_count; //0 if not specified
}			t_table;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long		last_eat;
	int			is_alive;
	int			is_full;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	td;
	t_table		*table;
}			t_philo;

int		is_args_pnum(int argc, char **argv);
t_table	init_table(int argc, char **argv);
t_philo	*init_philos(t_table *table, t_fork *forks);
t_fork	*init_forks(t_table *table);

long	get_ms(void);
void	ft_usleep(long ms);
int		ft_atoi(char *str);
void	start_dinner(t_table *table, t_philo *philos);
void	*monitor(void *v_philos);

#endif
