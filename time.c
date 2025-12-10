#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>

long get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
	long res;
	long secs;
	long usecs;
	long factor;

	factor = 1000000;
	secs = (end.tv_sec - start.tv_sec) * factor;
	usecs = (end.tv_usec - start.tv_usec);
	res =  secs + usecs;
	return (res);
}

void precise_usleep(long usec)
{
	struct timeval start;
	struct timeval current;
	long elapsed;
	long rem;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

/*
int main(void)
{
	struct timeval start;
	struct timeval end;
	long seconds;
	long microseconds;
	double elapsed;

	gettimeofday(&start, NULL);
	precise_usleep(500000);
	gettimeofday(&end, NULL);

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds + microseconds * 1e-6;

	printf("Expected sleep duration 0.5 seconds\n");
	printf("Actual custom sleep duration %f seconds\n", elapsed);

	gettimeofday(&start, NULL);
	usleep(500000)m
	gettimeofday(&end, NULL);
	
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds + microseconds * 1e-6;

	printf("Actual usleep duration %f seconds\n\n", elapsed);
	return (0);
}
*/
