/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:44 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/09 22:16:51 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_error(void)
{
	write(2, "Error\n", 6);
	return (0);
}

void *routine(void *data)
{
    int id;
    t_philo *dt = (t_philo *)data;

    id = dt->id;

    int i = (dt->id + 1) % dt->data->philo_num;
    while (1)
    {
        pthread_mutex_lock(&dt->data_race);
        pthread_mutex_lock(&dt->data->forkss[i]);
        msg_printer(dt, get_time(), TAKING_FORK, id + 1);
        pthread_mutex_lock(&dt->data->forkss[dt->id]);
        msg_printer(dt, get_time(), TAKING_FORK, id + 1);
        pthread_mutex_unlock(&dt->data_race);
        
        dt->last_eating = get_time() - dt->data->t0;
        msg_printer(dt, get_time(), EATING, id + 1);
        ft_usleep(dt->data->eat_time);
        msg_printer(dt, get_time(), SLEEPING, id + 1);
        
        pthread_mutex_lock(&dt->data_race);
        pthread_mutex_unlock(&dt->data->forkss[dt->id]);
        pthread_mutex_unlock(&dt->data->forkss[i]);
        
        dt->number_of_meals += 1;
        pthread_mutex_unlock(&dt->data_race);
        
        ft_usleep(dt->data->sleep_time);
        msg_printer(dt, get_time(), THINKING, id + 1);
    }
}

void	msg_printer(t_philo *philo, size_t timestamp, int action, int id)
{
	pthread_mutex_lock(&philo->data->write);
	timestamp++;
	if (action == TAKING_FORK)
		printf("%lld ms: philo number : %d has taken a fork 🍽\n", get_time() - philo->data->t0, id);
	else if (action == EATING)
		printf("%lld ms: philo number : %d is eating 🍕\n", get_time() - philo->data->t0, id);
	else if (action == SLEEPING)
		printf("%lld ms: philo number : %d is sleeping 💤\n", get_time() - philo->data->t0, id);
	else if (action == THINKING)
		printf("%lld ms: philo number : %d is thinking 💭\n", get_time() - philo->data->t0, id);
	else if (action == DIED)
	{
		printf("%lld ms: philo number : %d died 💀\n",get_time() - philo->data->t0, id);
		return ;
	}
	else if (action == OVER)
		printf("%lld ms: philo number : %d has finished his meals 🤢\n",get_time() - philo->data->t0, id);
	pthread_mutex_unlock(&philo->data->write);
}
int main(int ac, char **av)
{

	t_data *dt = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (1);
	if (check_valid_args(av))
		return (1);
	if (initialization(dt, av, ac))
		return (1);
	int a  = 0;
	if (dt->philo_num == 1)
	{
		ft_error();
		return (0);
	}
	// dt->philos->last_eating = malloc(sizeof(long) * dt->philo_num);
	while (a < dt->philo_num)
	{
		if (a % 2 == 0)
		{
			dt->philos[a].id = a;
			dt->philos[a].start_time = get_time();
			pthread_create(&dt->tid[a], NULL, &routine,  &dt->philos[a]);
		}
		a++;
	}
	usleep(500);
	a = 0;
	while (a < dt->philo_num)
	{
		if (a % 2 == 1)
		{
			dt->philos[a].id = a;
			dt->philos[a].start_time = get_time();
			pthread_create(&dt->tid[a], NULL, &routine,  &dt->philos[a]);
		}
		a++;
	}
	last_checking(dt, dt->philos);
	return(0);
}