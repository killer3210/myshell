#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include"myshell.h"


//实现读取命令并存放在arglist中
char **cmd_read()
{
	char buffer[ARGS];
	char c;
	int pos=0;
	char *p=buffer;
	int number=0;
	int len;
	char *start;
	char buf[ARGS];
	getcwd(buf,sizeof(buf));
	printf("root@killer:%s# ",buf);
	while(1)
	{
		c=getchar();
		if(c!='\n' && c != EOF)
			buffer[pos++]=c;
		else
		{
			buffer[pos++]='\0';
			break;
		
		}
	
	}//读取的字符存放在buffer中
	while(*p != '\0')
	{
		while(*p == ' ' || *p == '\t')
		{
			p++;
		}
		start = p;
		len=1;
		c=*++p;
		while(c != '\0' && c != ' ' && c != '\t')
		{
			len++;
			c=*++p;

		}
		arglist[number]=(char *)malloc(len+1);
		strncpy(arglist[number],start,len);
		arglist[number][len]='\0';
		number++;

	}//将buffer中的字符进行解析存放在arglist中
	return arglist;
}


//用execvp函数执行命令，通过fork()和execvp()配合实现
void cmd_exec()
{
	int ret_fork;
	int child_status;//子进程状态
	ret_fork=fork();
	if(ret_fork == 0)
	{
		execvp(arglist[0],arglist);
		perror("execvp_error");

	}
	else if(ret_fork > 0)
	{
		if(wait(&child_status)==-1) //等待子进程
			perror("wait");

	}
	else
	{
		perror("fork error");
	}

}

//cd命令的实现
void cd(char *path)
{
	chdir(path);//利用chdir函数实现切换工作目录
	char buf[ARGS];
	getcwd(buf,sizeof(buf));//getcwd读取当前工作目录
	printf("current working directory:%s\n",buf);

}


//打印环境变量
void env()
{	int i=0;
	extern char **environ;
	for(i=0;environ[i] != NULL ;i++)
		printf("environ:%s\n",environ[i]);
			

}


//帮助
void help()
{
	printf("welcome to myshell!\n");
	printf("you can use the following command:\n");
	printf("\"ls +all parameter\"  support all its parameters to list directories\n");
	printf("\"cd +path\"   change directory\n");
	printf("\"quit\"  to exit the shell\n");
	printf("\"environ\"  list all envrionment strings");
	printf("\"clear\"   clear the screen\n");
	printf("\"pwd\"  print working directory\n");
	printf("\"mkdir\"  make a new directory\n");
	printf("\"rm\"  remove a directory or file\n");
	printf("\"date\" print current time\n");
	printf("you can use all commonds supported by the execvp function\n");
}
