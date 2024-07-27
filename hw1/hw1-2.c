#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024

void ls_cmd(char *arg[]){
	int show_hidden=0,number=0;
	for (int i = 1; arg[i]!=NULL; i++) {
        if (strcmp(arg[i], "-a") == 0) {
            show_hidden = 1;
        } else if (strcmp(arg[i], "-l") == 0) {
            number = 1;
        } else if (strcmp(arg[i], "-al") == 0) {
            number = 1;
			show_hidden = 1;
        } 
    }
	if(show_hidden&&number){
		if (execl("/bin/ls", "ls","-l","-a", NULL)== -1) {
			perror("ls 失敗");
			return;
		}
	}
	else if(!show_hidden&&number){
		if (execl("/bin/ls", "ls","-l", NULL)== -1) {
			perror("ls 失敗");
			return;
		}
	}else if(show_hidden&&!number){
		if (execl("/bin/ls", "ls","-a", NULL)== -1) {
			perror("ls 失敗");
			return;
		}
	}else{
		if (execl("/bin/ls","ls", NULL)== -1) {
			perror("ls 失敗");
			return;
		}
	}




}

int main(int argc, char *argv[]) {
	char *arg[MAX_LINE/2+1];  // command line arguments
	char current_path[MAX_LINE];
	int should_run = 1;  // flag to determine when to exit program
	char inputBuffer[MAX_LINE];
	DIR *directory;
    struct dirent *entry;
	pid_t  pid;

	while(should_run){
		printf("osh> ");
		fflush(stdout);
		
		
		// get input from user
		read(STDIN_FILENO, inputBuffer, MAX_LINE);
		
		// tokenize user input 
		int i = 0;
		char *p = strtok(inputBuffer, " ");
		while (p != NULL) {
			arg[i] = p;
			char *pos;
			if ((pos = strchr(arg[i], '\n')) != NULL) {
				*pos = '\0';
			}
			p = strtok(NULL, " ");
			i++;
		}
		arg[i] = NULL;
		
		//ls
		if (strcmp(arg[0], "ls") == 0) {
        // 讀取目錄內容並列印
			pid = fork();	
			if (pid < 0) {
				perror("fork 失败");
				return 1;
			} else if (pid == 0) {
				ls_cmd(arg);
				return 1;
			} else {
				wait(NULL);
			}
				
    	} 

		//cat
		if (strcmp(arg[0], "cat") == 0) {
			pid = fork();
			if (pid < 0) {
				perror("fork 失败");
				return 1;
			} else if (pid == 0) {
				if(arg[1]!=NULL){
					const char *file_name = arg[1];
					if (execl("/bin/cat", "cat",file_name, NULL)== -1) {
						perror("cat 失敗");
						return 1;
					}
				}else{
					printf("請輸入檔名\n");
					return 1;
				}
			} else {
				wait(NULL);
			}
				
    	} 

		//date
		if (strcmp(arg[0], "date") == 0) {
			pid = fork();
			if (pid < 0) {
				perror("fork 失败");
				return 1;
			} else if (pid == 0) {
				if (execl("/bin/date", "date", NULL)== -1) {
					perror("date 失敗");
					return 1;
				}
			} else {
				wait(NULL);
			}
				
    	}

		//ps
		if (strcmp(arg[0], "ps") == 0) {
			pid = fork();
			if (pid < 0) {
				perror("fork 失败");
				return 1;
			} else if (pid == 0) {
				if(arg[1]!=NULL && strcmp(arg[1], "-f") == 0){
					if (execl("/bin/ps", "ps","-f", NULL)== -1) {
						perror("ps 失敗");
						return 1;
					}
				}
				else{
					if (execl("/bin/ps", "ps", NULL)== -1) {
						perror("ps 失敗");
						return 1;
					}
				}
			} else {
				wait(NULL);
			}
				
    	}



		//pwd
		if (strcmp(arg[0], "pwd") == 0) {
			pid = fork();
			if (pid < 0) {
				perror("fork 失败");
				return 1;
			} else if (pid == 0) {
				if (execl("/bin/pwd", "pwd", NULL)== -1) {
					perror("pwd 失敗");
					return 1;
				}
			} else {
				wait(NULL);
			}
		 	
    	} 

		// exit command
		if (strcmp(arg[0], "exit") == 0) {		
			printf("Process end\n");
			return 0;
		}
		
		
	}
	return 0;
}
