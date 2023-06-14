/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sonar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:05:43 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/14 14:46:42 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_data *data, t_philo *philo)
{
	int	a;
	int	j;

	a = -1;
	j = 0;
	if (data->meals_nb == 0)
		return (1);
	else if (data->meals_nb != -1)
	{
		while (++a < data->philo_num)
		{
			pthread_mutex_lock(philo[a].data_race2);
			if (philo[a].number_of_meals == data->meals_nb)
				j++;
			pthread_mutex_unlock(philo[a].data_race2);
		}
		if (j == data->philo_num)
		{
			printf("the philosophers have finished their meals 🤢\n");
			return (1);
		}
	}
	return (0);
}

int	check_death(t_data *data, t_philo *philo)
{
	int					a;
	unsigned long long	j;
	unsigned long long	r;
	int					d;

	a = -1;
	while (++a < data->philo_num)
	{
		pthread_mutex_lock(philo[a].data_race2);
		j = get_time() - data->t0;
		d = philo[a].dead;
		r = philo[a].last_eating;
		pthread_mutex_unlock(philo[a].data_race2);
		if ((j - r) >= data->death_time && d == 1)
		{
			msg_printer(philo, get_time(), DIED, philo->id + 1);
			return (1);
		}
	}
	return (0);
}

int	last_checking(t_data *data, t_philo *philo)
{
	usleep(100);
	while (1)
	{
		if (check_meals(data, philo))
			return (1);
		if (check_death(data, philo))
			return (1);
	}
	return (0);
}

void	creating_thread(t_data *dt)
{
	while (dt->a < dt->philo_num)
	{
		if (dt->a % 2 == 0)
		{
			dt->philos[dt->a].id = dt->a;
			dt->philos[dt->a].start_time = get_time();
			pthread_create(&dt->tid[dt->a], NULL, &routine, &dt->philos[dt->a]);
			pthread_detach(dt->tid[dt->a]);
		}
		dt->a++;
	}
	usleep(500);
	dt->a = 0;
	while (dt->a < dt->philo_num)
	{
		if (dt->a % 2 == 1)
		{
			dt->philos[dt->a].id = dt->a;
			dt->philos[dt->a].start_time = get_time();
			pthread_create(&dt->tid[dt->a], NULL, &routine, &dt->philos[dt->a]);
			pthread_detach(dt->tid[dt->a]);
		}
		dt->a++;
	}
}

void	first_part_of_rotine(t_philo *dt)
{
	pthread_mutex_lock(&dt->data->forkss[dt->i]);
	msg_printer(dt, get_time(), TAKING_FORK, dt->id2 + 1);
	pthread_mutex_lock(&dt->data->forkss[dt->id]);
	msg_printer(dt, get_time(), TAKING_FORK, dt->id2 + 1);
	msg_printer(dt, get_time(), EATING, dt->id2 + 1);
	pthread_mutex_lock(dt->data_race2);
	dt->last_eating = get_time() - dt->data->t0;
	pthread_mutex_unlock(dt->data_race2);
	ft_usleep(dt->data->eat_time);
	dt->eat = dt->eat + 1;
	msg_printer(dt, get_time(), SLEEPING, dt->id2 + 1);
	pthread_mutex_unlock(&dt->data->forkss[dt->id]);
	pthread_mutex_unlock(&dt->data->forkss[dt->i]);
}
