#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>

long get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
	long res;

	res = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
	return (res);
}

void precise_usleep(long usec)
{
	struct timeval start;
	struct timeval current;
	long elapsed;
	long rem;

	gettimeofday(&start, NULL);
	do {
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem < 1000)
			usleep(rem / 2);
	} while (elapsed < usec);

}


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
	printf("Expected sleep duration 5.0 seconds\n");
	printf("Actual custom sleep duration %f seconds\n", elapsed);
	gettimeofday(&start, NULL);
	usleep(500000);
	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds + microseconds * 1e-6;
	printf("Actual usleep duration %f seconds\n\n", elapsed);
	return (0);
}
