/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:02:28 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/03 01:19:50 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// int	forks_initialization(t_data *data)
// {
// 	int	i;

// 	i = 0;

// 	return (0);
// }

void	philos_initialization(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		//data->philos[i].id = i;
		// data->philos[i].time_to_die = data->death_time;
		// data->philos[i].eat_cont = 0;
		// data->philos[i].eating = 0;
		// data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}


int	data_initialization(t_data *data, char **av, int ac)
{
	int a = 0;
	data->philo_num = (int) ft_atoi(av[1]);
	data->death_time = (u_int64_t) ft_atoi(av[2]);
	data->eat_time = (u_int64_t) ft_atoi(av[3]);
	data->sleep_time = (u_int64_t) ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = (int) ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
			ft_error();
	data->forkss = malloc(sizeof(pthread_mutex_t) * (data->philo_num ));
	if (!data->forkss)
		ft_error();
	//data->forkss[data->philo_num] = NULL;
	while (a < data->philo_num)
		pthread_mutex_init(&data->forkss[a++], NULL);
	data->dead = 0;
	data->finish = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->t0 = get_time();
	return (0);
}