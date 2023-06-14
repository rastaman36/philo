/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:55:03 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/14 22:46:17 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_valid_args(char **argv)
{
	int	i;
	int	n;

	i = 1;
	while (argv[i])
	{
		n = 0;
		while (ft_strlen(argv[i]) > n)
		{
			if (!ft_isdigit(argv[i][n]))
				return (1);
			if (argv[i][n] == ' ')
				return (1);
			n++;
		}
		i++;
	}
	return (0);
}
