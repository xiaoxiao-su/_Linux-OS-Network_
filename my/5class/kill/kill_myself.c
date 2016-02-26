#include <stdio.h>

void handler(int sig)
{
	
}
int main()
{
	signal(2,handler);
}
