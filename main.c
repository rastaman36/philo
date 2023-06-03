/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:44 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/03 02:29:00 by mochaoui         ###   ########.fr       */
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
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		ft_error();
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		ft_error();
	printf("%d\n", data->philo_num);
	return (0);
}


int	initialization(t_data *data, char **av, int ac)
{
	if (data_initialization(data, av, ac))
		return (1);
	if (allocation_data(data))
		return (1);
	// if (forks_initialization(data))
	// 	return (1);
	philos_initialization(data);
	return (0);
}

// void	create_your_routine(t_data *dt, int id)
// {
// 		pthread_mutex_t *l_even;
// 		pthread_mutex_t *r_even;

// 		l_even = dt->forkss + id;
// 		r_even = dt->forkss + ((id + 1) %  dt->philo_num);
// 		pthread_mutex_lock(l_even);
// 		msg_printer(dt->philos, get_time(), TAKING_FORK, id + 1);
// 		pthread_mutex_lock(r_even);
// 		pthread_mutex_lock(&dt->philos->lock);
// 		dt->last_eating[id]= get_time();
// 		pthread_mutex_unlock(&dt->philos->lock);
// 		msg_printer(dt->philos, get_time(), TAKING_FORK, id + 1);
// 		ft_usleep(dt->eat_time);
// 		msg_printer(dt->philos, get_time(), EATING, id + 1);
// 		pthread_mutex_unlock(l_even);
// 		pthread_mutex_unlock(r_even);
// 		pthread_mutex_lock(&dt->philos->lock);
// 		msg_printer(dt->philos, get_time(), SLEEPING, id + 1);
// 		ft_usleep(dt->sleep_time);
// 		pthread_mutex_unlock(&dt->philos->lock);
// 		msg_printer(dt->philos, get_time(), THINKING, id + 1);
// }
	

void    *routine(void *data)
{
	int id;
	t_data *dt = (t_data *)data;
	pthread_mutex_lock(&dt->philos->lock);
	//printf("[%zu]\n", dt->philos->id);
	id = dt->philos->id;
	// pthread_mutex_t	*r_fork;
	// pthread_mutex_t	*l_fork;
	dt->philos->r_fork = dt->forkss + id;
	dt->philos->l_fork = dt->forkss + ((id + 1) %  dt->philo_num);

	pthread_mutex_unlock(&dt->philos->lock);
	//printf("\\%d\\\n", id);
    while (1)
    {
		//printf("%d------------\n", id);
		pthread_mutex_lock(dt->philos->r_fork);
		msg_printer(dt->philos, get_time(), TAKING_FORK, id + 1);
		pthread_mutex_lock(dt->philos->l_fork);
		pthread_mutex_lock(&dt->philos->lock);
		dt->last_eating[id]= get_time();
		pthread_mutex_unlock(&dt->philos->lock);
		msg_printer(dt->philos, get_time(), TAKING_FORK, id + 1);
		ft_usleep(dt->eat_time);
		msg_printer(dt->philos, get_time(), EATING, id + 1);
		pthread_mutex_unlock(dt->philos->l_fork);
		pthread_mutex_unlock(dt->philos->r_fork);
		pthread_mutex_lock(&dt->philos->lock);
		msg_printer(dt->philos, get_time(), SLEEPING, id + 1);
		pthread_mutex_unlock(&dt->philos->lock);
		ft_usleep(dt->sleep_time);
		msg_printer(dt->philos, get_time(), THINKING, id + 1);
		dt->philos->data = dt;
    }
}


void	msg_printer(t_philo *philo, size_t timestamp, int action, int id)
{
	// pthread_mutex_lock(&philo->data->write);
	timestamp++;
	if (action == TAKING_FORK)
		printf("%lld ms: %d has taken a fork 🍽\n", get_time() - philo->data->t0, id);
	else if (action == EATING)
		printf("%lld ms: %d is eating 🍕\n", get_time() - philo->data->t0, id);
	else if (action == SLEEPING)
		printf("%lld ms: %d is sleeping 💤\n", get_time() - philo->data->t0, id);
	else if (action == THINKING)
		printf("%lld ms: %d is thinking 💭\n", get_time() - philo->data->t0, id);
	else if (action == DIED)
		printf("%lld ms: %d died 💀\n",get_time() - philo->data->t0, id);
	else if (action == OVER)
		printf("%lld ms: %d has finished his meals 🤢\n",get_time() - philo->data->t0, id);
	// pthread_mutex_unlock(&philo->data->write);
}
 
// int	deth_threads(t_data *philo)
// {
// 	int i = 0;
// 	while(1)
// 	{
// 		while (i < philo->philo_num)
// 		{
// 			//pthread_mutex_lock(&philo->philos->lock);
// 			if (get_time() - philo->last_eating[i] >= philo->death_time)
// 			{
// 				msg_printer(philo->philos, get_time(), DIED);
// 				return (0);
// 			}
// 			//pthread_mutex_unlock(&philo->philos->lock);
// 			i++;
// 		}
// 	}
// }
int main(int ac, char **av)
{
	t_philo *philo;

	t_data *dt = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo));
	if (ac < 5 || ac > 6)
		return (1);
	if (check_valid_args(av))
		return (1);
	if (initialization(dt, av, ac))
		return (1);
	int a  = 0;
	dt->last_eating = malloc(sizeof(unsigned long) * dt->philo_num);
	while (a < dt->philo_num)
	{
		pthread_mutex_lock(&dt->philos->lock);
		dt->philos->id = a;
		dt->last_eating[a] = get_time();
		pthread_mutex_unlock(&dt->philos->lock);
		pthread_create(&dt->tid[a], NULL, &routine, dt);
		usleep(500);
		a++;
	}
	while (1);
	//eturn(deth_threads(dt));
}