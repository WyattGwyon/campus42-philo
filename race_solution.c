#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		//read value in mails
		//increment value
		//write mails
	}
	return (&mails);
}

int main(int argc, char *argv[])
{
	pthread_t th[4];
	
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
			return (1);
		printf("Thread %d has started\n", i);
	}
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL))
			return (2);
		printf("Thread %d has ended\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
