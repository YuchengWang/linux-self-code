#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <sys/mman.h>

int page_size;
#define PAGE_SIZE page_size
#define PAGE_MASK (~(PAGE_SIZE-1))
void get_var (unsigned long addr) {
	off_t ptr = addr & ~(PAGE_MASK);
	off_t offset = addr & PAGE_MASK;
	int i = 0;
	char *map;
	static int kfd = -1;
	kfd = open("/dev/kmem",O_RDONLY);
	if (kfd < 0) {
		perror("open");
		exit(0);
	}
	map = mmap(NULL,PAGE_SIZE,PROT_READ,MAP_SHARED,kfd,offset);
	if (map == MAP_FAILED) {
		perror("mmap");
		exit(-1);
	}
	/* 假定这里是字符串 */
	printf("%s\n",map+ptr);
	return;
}

int main(int argc, char **argv)
{
	FILE *fp;
	char addr_str[11]="0x";
	char var[51];
	unsigned long addr;
	char ch;
	int r;

	if (argc != 2) {
		fprintf(stderr,"usage: %s System.map\n",argv[0]);
		exit(-1);
	}
	if ((fp = fopen(argv[1],"r")) == NULL) {
		perror("fopen");
		exit(-1);
	}
	do {
		r = fscanf(fp,"%8s %c %50s\n",&addr_str[2],&ch,var);

		if (strcmp(var,"noioapicquirk")==0)
			break;
	} while(r > 0);
	if (r < 0) {
		perror("could not find modprobe_path");
		exit(-1);
	}
	page_size = getpagesize();
	addr = strtoul(addr_str,NULL,16);
	printf("found modprobe_path at (%s) %08lx\n",addr_str,addr);
	get_var(addr);
}
