/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:31:26 by mochaoui          #+#    #+#             */
/*   Updated: 2023/04/24 09:19:33 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void*    roll_dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("Thread result : %p\n", result);
    return (void *)result;
}

int main(int ac, char **av)
{
    int* res;
    srand(time(NULL));
    pthread_t   th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        return (1);
    if (pthread_join(th, (void **) &res) != 0)
        return (2);
    printf("Main res : %p\n", res);
    printf("resulst %d\n", *res);
    return (0);
}