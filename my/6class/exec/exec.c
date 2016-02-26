#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	pid_t id = fork();
	if(id == 0){
		execl("/bin/ls","ls","-al","../exec",NULL);//如果execl函数执行成功，就不会执行printf语句，没有返回

		execlp("com.out","com.out",NULL);//将从根目录起到当前文件的路径如/home/xiaoxiaosu/class/6class/exec/bin（com.out在bin目录底下）添加到PATH即可，函数名带p，表示运行时在环境变量下查找适用路径
		//execlp(argv[1],argv[1],argv[2],NULL);//通过命令行传参数

		char* argv[] = {"ls","-al","./bin",NULL};
		char* my_env[] = {"PATH=/I/AM/PATH",NULL};
		execle("/home/xiaoxiaosu/class/6class/exec/bin/com.out","com.out",NULL,my_env);
		//execle("/bin/ls","ls","-al","./bin",my_env,NULL);

		execv("/bin/ls",argv);

		execvp("/bin/ls",argv);
		execve("/bin/ls",argv,my_env);

		printf("haha,I am here...\n");//当execl执行错误才会输出这条语句
		perror("error");
		exit(0);
	}else{
		wait(NULL);
	}
	return 0;
}

//以上主函数中的execl、execlp、execle、execv、execvp、execve函数不能同存

