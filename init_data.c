/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:02:28 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/14 22:44:41 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_initialization(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].number_of_meals = 0;
		data->philos[i].last_eating = 0;
		data->philos[i].data_race2 = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->philos[i].data_race2, NULL);
		data->philos[i].dead = 1;
		i++;
	}
}

int	data_initialization(t_data *data, char **av, int ac)
{
	int	a;

	a = 0;
	data->philo_num = (int) ft_atoi(av[1]);
	data->death_time = (u_int64_t) ft_atoi(av[2]);
	data->eat_time = (u_int64_t) ft_atoi(av[3]);
	data->sleep_time = (u_int64_t) ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = (int) ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	if (data->meals_nb == 0 || data->death_time == 0
		|| data->eat_time == 0 || data->sleep_time == 0 || data->philo_num == 0)
		return (1);
	if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (0);
	data->forkss = malloc(sizeof(pthread_mutex_t) * (data->philo_num));
	if (!data->forkss)
		return (0);
	while (a < data->philo_num)
		pthread_mutex_init(&data->forkss[a++], NULL);
	pthread_mutex_init(&data->write, NULL);
	data->t0 = get_time();
	return (0);
}

int	allocation_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (0);
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		return (0);
	return (0);
}

int	initialization(t_data *data, char **av, int ac)
{
	if (data_initialization(data, av, ac))
		return (1);
	if (allocation_data(data))
		return (1);
	philos_initialization(data);
	return (0);
}
