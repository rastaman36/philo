/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:34:44 by mochaoui          #+#    #+#             */
/*   Updated: 2023/04/27 13:51:41 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		perror("FAIL");
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}

void    *routine(t_philo *dt)
{

    pthread_mutex_t	mutex;
	pthread_mutex_init(&mutex, NULL);

    while ()
    {
        dt->data->start_time = get_time();
        
    //we start by thinking of philo(he think whenever he can't eat)
    
                
                //when he think display "Philo x is thinking"
    
    


    // here eating / 4 :
    
    // 1 : -----> picking 2 forks

        pthread_mutex_lock(&mutex);
        
                
    

    // 2 : ------> eating

                //when he eat update the status and display "Philo x is eat"


    // 3 : -------> dropping the forks


    // 4 : --------> sleping 


                    //when  he slep update the status and display "Philo x is sleep"
    
    }    
}

int main(int ac , char **av)
{
    t_philo *dt;

    dt = ft_calloc(1, sizeof(t_philo));
    if (ac < 5 || ac > 6)
        return (1);
    


    // pthread_t   tid;
    // pthread_create(&tid, NULL, &routine, &dt);

    u_int64_t r = get_time();
    printf("%llu", r);
    
    

    

}