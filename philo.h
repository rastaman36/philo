/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:59 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/14 14:46:51 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	OVER,
}				t_action;

typedef struct s_philo
{
	struct s_data		*data;
	int					id;
	unsigned long long	last_eating;
	int					number_of_meals;
	u_int64_t			start_time;
	pthread_mutex_t		*data_race2;
	int					dead;
	int					id2;
	int					eat;
	int					i;	
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	t_philo			*philos;
	pthread_mutex_t	*forkss;
	pthread_mutex_t	write;
	pthread_mutex_t	write2;
	unsigned long	t0;
	int				a;
}	t_data;

void		philos_initialization(t_data *data);
int			data_initialization(t_data *data, char **av, int ac);
int			ft_atoi(const char *str);
int			initialization(t_data *data, char **av, int ac);
int			allocation_data(t_data *data);
void		*ft_calloc(size_t count, size_t size);
u_int64_t	get_time(void);
int			ft_usleep(useconds_t time);
int			check_valid_args(char **argv);
int			ft_error(void);
void		msg_printer(t_philo *philo, size_t timestamp, int action, int id);
int			check_death(t_data *data, t_philo *philo);
int			check_meals(t_data *data, t_philo *philo);
int			last_checking(t_data *data, t_philo *philo);
void		*routine(void *data);
void		creating_thread(t_data *dt);
void		first_part_of_rotine(t_philo *dt);

#endif