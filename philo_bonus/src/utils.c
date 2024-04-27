/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:48:26 by hiono             #+#    #+#             */
/*   Updated: 2024/04/26 19:30:21 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// display philosophers' action with id and timestamp
void	print_action(t_action action, t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp(philo->table);
	if (exclusive_get_bool(&philo->table->is_finished, &philo->table->lock))
		return ;
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
