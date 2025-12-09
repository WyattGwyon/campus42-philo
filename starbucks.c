#include <stdio.h>
#include <unistd.h>

void make_coffee(char *name)
{
	printf("Barrista %s is making coffee...\n", name);
	sleep(3);
	printf("Order Ready!\n");
}

int main(void)
{
	make_coffee("Luca");
	make_coffee("Paolo");
	return (0);
}
