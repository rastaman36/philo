/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:31:26 by mochaoui          #+#    #+#             */
/*   Updated: 2023/05/17 15:45:07 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(void)
{
	write(2, "Error\n", 6);
	return (0);
}

// int	allocation_data(t_data *data)
// {
// 	// data->tid = malloc(sizeof(pthread_t) * data->philo_num);
// 	// if (!data->tid)
// 	// 	ft_error();
// 	// data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
// 	// if (!data->forks)
// 	// 	ft_error();
// 	data->philos = malloc(sizeof(t_philo);
// 	if (!data->philos)
// 		ft_error();
// 	return (0);
// }

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		perror("FAIL");
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	print(char *str, t_philo *dt)
{
	printf(str, dt->id, get_time());
}

int main ()
{
    t_data *dt = malloc(sizeof(t_data));
    dt->philos = malloc(sizeof(t_philo));
    dt->philos->id  = 1;
    print("philo number %d is eating. time : %llu", dt->philos);
}