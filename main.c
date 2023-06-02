/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:44 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/01 17:22:44 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_error(void)
{
	write(2, "Error\n", 6);
	return (0);
}


int	allocation_data(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		ft_error();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		ft_error();
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		ft_error();
	return (0);
}


int	initialization(t_data *data, char **av, int ac)
{
	if (data_initialization(data, av, ac))
		return (1);
	if (allocation_data(data))
		return (1);
	if (forks_initialization(data))
		return (1);
	philos_initialization(data);
	return (0);
}


void    *routine(t_philo *dt)
{
    while (1)
    {
		
    
    }    
}


void	msg_printer(t_philo *philo, size_t timestamp, int action)
{
	// pthread_mutex_lock(&philo->data->write);
	if (action == TAKING_FORK)
		printf("%zu %zu has taken a fork 🍽\n", timestamp, philo->id);
	else if (action == EATING)
		printf("%zu %zu is eating 🍕\n", timestamp, philo->id);
	else if (action == SLEEPING)
		printf("%zu %zu is sleeping 💤\n", timestamp, philo->id);
	else if (action == THINKING)
		printf("%zu %zu is thinking 💭\n", timestamp, philo->id);
	else if (action == DIED)
		printf("%zu %zu died 💀\n", timestamp, philo->id);
	else if (action == OVER)
		printf("%zu %zu has finished his meals 🤢\n", timestamp, philo->id);
	// pthread_mutex_unlock(&philo->data->write);
}
 

int main(int ac, char **av)
{
    t_data *dt;
	t_philo *philo;


	if (ac < 5 || ac > 6)
		return (1);
	if (check_valid_args(av))
		return (1);
	printf("clear");
	if (initialization(dt, av, ac))
		return (1);


}