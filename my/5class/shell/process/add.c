#include <stdio.h>
#include <malloc.h>

int g_val;
int g_arr[3] = {0};

void fun()
{
	printf("hello world\n");
}

int main()
{
	static int a = 10;
	
	return 0;
}
