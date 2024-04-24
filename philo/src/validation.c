/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:22:19 by hiono             #+#    #+#             */
/*   Updated: 2024/04/19 18:30:07 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_str_pnum(char *str)
{
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

int	is_args_pnum(int argc, char **argv)
{
	while (0 < --argc)
	{
		if (!is_str_pnum(argv[argc]))
			return (0);
	}
	return (1);
}
