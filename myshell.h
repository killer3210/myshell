#define ARGS 512

#define ARG 20

char *arglist[ARG];//用于存放读取的命令
void cd(char *path);
char **cmd_read();
void cmd_exec();
void env();
void help();