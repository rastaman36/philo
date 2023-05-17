/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:44 by mochaoui          #+#    #+#             */
/*   Updated: 2023/05/17 15:49:38 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void    print_status(int n)
{
    if (n == 1)
        printf("philo has taken a fork");
	else if (n == 2)
		printf("philo is eating");
	else if (n == 3)
		printf("phile is sleeping");
	else if (n == 4)
		printf("philo is thinking");
	else if (n == 5)
		printf("philo is died");
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > __LONG_LONG_MAX__ && sign == -1)
			return (0);
		if (res > __LONG_LONG_MAX__ && sign == 1)
			return (-1);
		i++;
	}
	return (res * sign);
}

int	 check_valid_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				ft_error();
			j++;
		}
		i++;
	}
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

int	forks_initialization(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_num - 1];
	i = 1;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	philos_initialization(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	data_initialization(t_data *data, char **av, int ac)
{
	data->philo_num = (int) ft_atoi(av[1]);
	data->death_time = (u_int64_t) ft_atoi(av[2]);
	data->eat_time = (u_int64_t) ft_atoi(av[3]);
	data->sleep_time = (u_int64_t) ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = (int) ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
			ft_error();
	data->dead = 0;
	data->finish = 0;
	// pthread_mutex_init(&data->write, NULL);
	// pthread_mutex_init(&data->lock, NULL);
	return (0);
}

// void	initialization(t_data *data, char **av, int ac)
// {
// 	data_initialization(data, av, ac);
// 	allocation_data(data);
// 	forks_initialization(data);
// 	philos_initialization(data);
// }

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)malloc(count * size);
	if (!s)
		return (NULL);
	while (i < (count * size))
	{
		s[i] = 0;
		i++;
	}
	return (s);
}


u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		perror("FAIL");
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}

void	print(char *str, t_philo *dt)
{
	printf(str, get_time(), &dt->id);
}

void    *routine(t_philo *dt)
{
    while (1)
    {
    // 1 : -----> picking 2 forks

        pthread_mutex_lock(dt->l_fork);
		pthread_mutex_lock(dt->r_fork);
		

		
		
        
                
    

    // 2 : ------> eating

                //when he eat update the status and display "Philo x is eat"


    // 3 : -------> dropping the forks


    // 4 : --------> sleping 


                    //when  he slep update the status and display "Philo x is sleep"
    
    }    
}

int main(int ac, char **av)
{
    t_data *dt;

    int a = 0;
	
	// if (ac < 5 || ac > 6)
	// 	return (1);
	print("philo is eating %llu number %d", dt->philos);
	// check_valid_args(av);
	// initialization(dt, av, ac);
	// while (a < dt->philo_num)
	// {
		
	// }
	// u_int64_t r = get_time();
    // printf("%llu", r);
	
	
    // while (a < ac)
	// {
	// 	if (!input_checker)
	// 		perror("error");
    //     if (ac < 5 || ac > 6)
    //         return (1);
	// 	a++;
	// }
    


    // pthread_t   tid;
    // pthread_create(&tid, NULL, &routine, &dt);

 
    

}