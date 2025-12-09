#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *roll_dice()
{
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = value;
	printf("thread result: %p\n", result);
	//printf("%d\n", value);
	return ((void *) result);
}

int main(int ac, char *av[])
{
	int *res;

	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void**) &res) != 0)
		return 2;
	printf("main result: %p\n", res);
	printf("Results: %d\n", *res);
	free(res);
	return 0;
}
