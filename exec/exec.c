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


（1）不带字母p (表示path)的exec函数 第一个参数必须是程序的相对路径或绝对路径,例如
"/bin/ls"或"./a.out",而不能 是"ls"或"a.out"。对于带字母p的函数: 如果参数中包含/,则
将其视为路径名。 否则视为不带路径的程序名,在PATH环境变量的目录列表中搜索这
个程序。
（2）带有字母l( 表示list)的exec函数要求将新程序的每个命令行参数都当作一个参数传给
它,命令行 参数的个数是可变的,因此函数原型中有...,...中的最后一个可变参数应该是
NULL, 起sentinel的作用。
（3）带有字母v( 表示vector)的函数,则应该先构造一个指向各参数的指针数 组,然后将该数
组的首地址当作参数传给它,数组中的最后一个指针也应该是NULL,就像main函数 的
argv参数或者环境变量表一样。
（4）对于以e (表示environment)结尾的exec函数,可以把一份新的环境变量表传给它,其他
exec函数仍使用当前的环境变量表执行新程序。