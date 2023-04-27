/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:20:59 by mochaoui          #+#    #+#             */
/*   Updated: 2023/04/25 15:26:55 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	valid_argument(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		ft_error();
	while (str && str[i])
	{
		if ((str[i] != ' ' && str[i] != '+') && (str[i] < '0'
				|| str[i] > '9'))
			ft_error();
		if ((str[i] == '+') && (str[i + 1] < '0'
				|| str[i + 1] > '9'))
			ft_error();
		i++;
		if ((str[i - 1] >= '0' && str[i - 1] <= '9') && (str[i] == '+'))
			ft_error();
	}
	return (1);
}