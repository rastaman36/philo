/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:59 by mochaoui          #+#    #+#             */
/*   Updated: 2023/06/03 01:00:04 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
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
	struct s_data	*data;
	pthread_t       t1;
	size_t          id;
	int             eat_cont;
	int             status;
	int             eating;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	pthread_t       *tid;
	int             philo_num;
	int             meals_nb;
	int             dead;
	int				finish;
	unsigned int 	*last_eating;
	t_philo         *philos;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
	pthread_mutex_t *forkss;
	pthread_mutex_t lock;
	pthread_mutex_t write;
	unsigned long t0;
} t_data;



int			forks_initialization(t_data *data);
void		philos_initialization(t_data *data);
int			data_initialization(t_data *data, char **av, int ac);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
u_int64_t	get_time(void);
int			ft_usleep(useconds_t time);
int	 		check_valid_args(char **argv);
int			ft_error(void);
void		msg_printer(t_philo *philo, size_t timestamp, int action, int id);


#endif