/*******************************************************************
file name：myshell.c myshell.h utility.c
author: killer
blog: killerli.cn
create time: 2020-04-28
function: 
	cmds:ls,rm,mkdir,pwd,environ,quit,pause,pwd,date...(use execvp()
****************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include"myshell.h"



int main()
{

	int i;
	while(1)
	{

		i=0;	
		
		cmd_read();
		if(!strcmp(arglist[0],"cd"))
			cd(arglist[1]);
		
		else if(!strcmp(arglist[0],"environ"))
			env();
		else if(!strcmp(arglist[0],"quit"))
			return 1;
		else if(!strcmp(arglist[0],"help"))
			help();
		else if(!strcmp(arglist[0],"pause"))
		{
			printf("please input \"enter\" to continue");
			getchar();//getchar卡住按任意键可继续
		
		}

		else//实现除上述命令外的其他命令
		{
			cmd_exec();
		
		}


		while(arglist[i])
		{
			free(arglist[i]);
			i++;
		}//free空间
	}

	return 0;
}