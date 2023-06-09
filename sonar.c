/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sonar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:05:43 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/09 22:28:49 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_meals(t_data *data, t_philo *philo)
{
    int a;
    int j;

    a = -1;
    j = 0;
    if (data->meals_nb == 0)
		return (1);
    else if (data->meals_nb != -1)
    {
        pthread_mutex_lock(&philo[a].data_race); 
        while (++a < data->philo_num)
        {
            if (philo[a].number_of_meals >= data->meals_nb)
                j++;
        }
        pthread_mutex_unlock(&philo[a].data_race);
        if (j == data->meals_nb)
        {
            msg_printer(philo, get_time(), OVER, philo->id + 1);
            return (1);
        }
    }
    return (0);
    
}

// int check_meals(t_data *data, t_philo *philo)
// {
//     int a;

//     a = -1;
//     while (++a < data->philo_num)
//     {
//         pthread_mutex_lock(&philo[a].data_race); // Lock the mutex before accessing meals_eaten
//         int meals_eaten = philo[a].meals_eaten; // Read meals_eaten
//         pthread_mutex_unlock(&philo[a].data_race); // Unlock the mutex after reading meals_eaten
        
//         if (meals_eaten < data->num_of_meals)
//             return (0);
//     }

//     return (1);
// }

// long	gettime(void)
// {
// 	struct timeval	current_time;

// 	gettimeofday(&current_time, NULL);
// 	return ((current_time.tv_usec + current_time.tv_sec * 1000000));
// }


int check_death(t_data *data, t_philo *philo)
{
    int a;
    unsigned long long j;

    a = -1;

    while (++a < data->philo_num)
    {
        pthread_mutex_lock(&philo[a].data_race); // Lock the mutex before accessing last_eating
        j = get_time() - data->t0;
        unsigned long long last_eating = philo[a].last_eating; // Read last_eating
        pthread_mutex_unlock(&philo[a].data_race); // Unlock the mutex after reading last_eating

        pthread_mutex_lock(&philo[a].data_race); // Lock the mutex before updating last_eating
        if ((j - last_eating) >= data->death_time)
        {
            msg_printer(philo, get_time(), DIED, philo->id + 1);
            pthread_mutex_unlock(&philo[a].data_race); // Unlock the mutex if a philosopher died
            return (1);
        }
        pthread_mutex_unlock(&philo[a].data_race); // Unlock the mutex after updating last_eating
    }

    return (0);
}

int     last_checking(t_data *data, t_philo *philo)
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