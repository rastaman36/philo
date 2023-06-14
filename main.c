/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:44 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/14 16:48:02 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(void)
{
	write(2, "Error\n", 6);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*dt;

	dt = (t_philo *)data;
	dt->eat = 0;
	dt->id = dt->id;
	dt->i = (dt->id + 1) % dt->data->philo_num;
	while (1)
	{
		first_part_of_rotine(dt);
		pthread_mutex_lock(dt->data_race2);
		dt->number_of_meals += 1;
		if (dt->eat == dt->data->meals_nb)
			dt->dead = 0;
		pthread_mutex_unlock(dt->data_race2);
		if (dt->eat == dt->data->meals_nb)
			return (NULL);
		ft_usleep(dt->data->sleep_time);
		msg_printer(dt, get_time(), THINKING, dt->id2 + 1);
	}
}

void	msg_printer(t_philo *philo, size_t timestamp, int action, int id)
{
	pthread_mutex_lock(&philo->data->write);
	timestamp++;
	if (action == TAKING_FORK)
		printf("%lld ms :----> philo number : %d has taken a fork 🍽\n", \
			get_time() - philo->data->t0, id);
	else if (action == EATING)
		printf("%lld ms :----> philo number : %d is eating 🍕\n", \
			get_time() - philo->data->t0, id);
	else if (action == SLEEPING)
		printf("%lld ms :----> philo number : %d is sleeping 💤\n", \
			get_time() - philo->data->t0, id);
	else if (action == THINKING)
		printf("%lld ms :----> philo number : %d is thinking 💭\n", \
			get_time() - philo->data->t0, id);
	else if (action == DIED)
	{
		printf("%lld ms :----> philo number : %d died 💀\n", \
			get_time() - philo->data->t0, id);
		return ;
	}
	else if (action == OVER)
		printf("%lld ms :----> philo number : %d has finished his meals 🤢\n", \
			get_time() - philo->data->t0, id);
	pthread_mutex_unlock(&philo->data->write);
}

int	main(int ac, char **av)
{
	t_data	*dt;

	dt = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (1);
	if (check_valid_args(av))
		return (1);
	if (initialization(dt, av, ac))
		return (1);
	dt->a = 0;
	if (dt->philo_num <= 1)
	{
		printf("%llu ms :----> philo number : %d died 💀\n", \
			dt->death_time, dt->philo_num);
		return (0);
	}
	creating_thread(dt);
	last_checking(dt, dt->philos);
	return (0);
}
