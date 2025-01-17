#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void helper(int sig)
{
	printf("ceci est just un warning\n ");
}
int main()
{
	signal(SIGINT,helper);

	while(1)
	{
		printf("salam ana gha kantester hadchi wach khedam\n ");
		sleep(1);
	}
}

