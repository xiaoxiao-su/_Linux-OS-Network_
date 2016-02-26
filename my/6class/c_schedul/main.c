#include <stdio.h>
//基于C语言的进度条
int main()
{
    char ch[] = "hello a";
    int index = 0;
    while(index<26)
    {
        printf("%s\r",ch);
		ch[6] += 1;
		fflush(stdout);
		index++;
		sleep(1);
    }
}
