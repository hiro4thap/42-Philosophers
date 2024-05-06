/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:48:26 by hiono             #+#    #+#             */
/*   Updated: 2024/05/06 14:52:31 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// display philosophers' action with id and timestamp
void	print_action(t_action action, t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp(philo->table);
	sem_wait(philo->table->message);
	if (action == TAKE_FORK)
		printf("%-8ld %4d has taken a fork\n", timestamp, philo->id);
	else if (action == EAT)
		printf("%-8ld %4d is eating\n", timestamp, philo->id);
	else if (action == SLEEP)
		printf("%-8ld %4d is sleeping\n", timestamp, philo->id);
	else if (action == THINK)
		printf("%-8ld %4d is thinking\n", timestamp, philo->id);
	else if (action == DIE)
		printf("%-8ld %4d died\n", timestamp, philo->id);
	if (action != DIE)
		sem_post(philo->table->message);
}

// atoi where inputs should be poisive numbers
int	ft_atoi(char *str)
{
	int	res;

	if (*str == '+')
		str++;
	res = 0;
	while (*str)
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res);
}
