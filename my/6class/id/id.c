#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>
int main()
{
	pid_t id = fork();
	if(id<0){
		printf("fork erroe\n");
		exit(1);
	}
	else if(id == 0){
		printf("child:\npid:%d\nppid:%d\nuid:%d\neuid:%d\ngid:%d\negid:%d\n",getpid(),getppid(),getuid(),geteuid(),getgid(),getegid());
	}else{
		printf("father:\npid:%d\nppid:%d\nuid:%d\neuid:%d\ngid:%d\negid:%d\n",getpid(),getppid(),getuid(),geteuid(),getgid(),getegid());
	}
	printf("i am a student\n");
	return 0;
}
