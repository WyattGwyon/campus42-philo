/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:22:05 by clouden           #+#    #+#             */
/*   Updated: 2025/11/30 17:37:26 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *routine()
{
	printf("test from threads\n");
	sleep(3);
	printf("ending thread\n");
	return (0);
}


int main(int ac, char *av[])
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return (0);
}
