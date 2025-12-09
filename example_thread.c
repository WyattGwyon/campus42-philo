#include <stdio.h>
#include <pthread.h>


int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thread_func, NULL);
	
}
