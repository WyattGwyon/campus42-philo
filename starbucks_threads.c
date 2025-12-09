#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#ifndef NUM
#define NUM 6
#endif

typedef struct s_philo_arg
{
	int id;
}	t_philo_arg;

void *eat(t_philo_arg *data)
{
	printf("Philo %d is eating\n", data->id);
	sleep(2);
	printf("Finished Eating!\n");
	return (NULL);
}

void *thread_func(void *arg)
{
	t_philo_arg *info  = (t_philo_arg *)arg;
	eat(arg);
	printf("thread id: %d\n", info->id);
	return (NULL);
}

int main()
{
	pthread_t barista[NUM];
	t_philo_arg args[NUM];

	for (int i = 0; i < NUM; i++)
	{
		args[i].id = i + 1;
		if (pthread_create(&barista[i], NULL, thread_func, &args[i]))
			return (1);
	}

	for (int i = 0; i < NUM; i++)
	{
		pthread_join(barista[i], NULL);
	}
}
