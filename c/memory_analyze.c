#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int get_info(char *s){
	pid_t pid;

	FILE *fp;
	char path[1024];
	char command[128];
	char *token;
	char *addr;

	pid = getpid();

	//printf("current pid %d\n", pid);
	sprintf(command, "cat /proc/%d/maps | grep %s", pid, s);

	/* Open the command for reading. */
	fp = popen(command, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);

		char *token=strtok(path," ");
		if(token!=NULL){
			printf("%s\n",token);
			while(token!=NULL){
				addr=strtok(token,"-");
				printf("%s\n",addr);
				token=strtok(NULL," ");
			}
		} 
	}

	/* close */
	pclose(fp);

	return 0;
}

int main(){
	void * p;
	int i;

	for(i=0; i<100; i++){
		get_info("heap");
		get_info("stack");
		void *p = sbrk(0);
		printf("current heap top:0x%08p \n", p);
		p = (void *)malloc(0x10*sizeof(int));
		printf("after malloc heap top:%08p\n", p);
	}

	return 0;
}
