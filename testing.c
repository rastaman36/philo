/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:31:26 by mochaoui          #+#    #+#             */
/*   Updated: 2023/05/31 16:58:21 by mochaoui         ###   ########.fr       */
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

void	ft_msg(t_philo *philo, size_t timestamp, int action)
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

int main ()
{
    t_data *dt = malloc(sizeof(t_data));
    dt->philos = malloc(sizeof(t_philo));
	ft_msg(dt->philos, get_time(), TAKING_FORK);
}