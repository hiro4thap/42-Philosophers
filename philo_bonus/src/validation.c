/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:22:19 by hiono             #+#    #+#             */
/*   Updated: 2024/05/07 13:21:46 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// check a string is positive number
int	is_str_pnum(char *str)
{
	if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (0);
		str++;
	}
	return (1);
}

// check all arguments are poisitve numbers
int	is_args_pnum(int argc, char **argv)
{
	while (0 < --argc)
	{
		if (!is_str_pnum(argv[argc]))
			return (0);
	}
	return (1);
}

// validate the arguments
// 1) number of arguments should be 5 or 6
// 2) each argument is positive numebr
// if not valid, exit program
void	validate_args(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("The number of arguments should be 4 or 5\n");
		exit (EXIT_FAILURE);
	}
	if (!is_args_pnum(argc, argv))
	{
		printf("All arguments should be positive numbers\n");
		exit (EXIT_FAILURE);
	}
}
