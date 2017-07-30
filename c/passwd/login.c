#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>
#include <crypt.h>

#define AUTH_SIZE 1024

int main(int argc, char* argv[])
{
	struct termios ts, ots;
	char userbuf[AUTH_SIZE];
	char passbuf[AUTH_SIZE];
	char cryptbuf[AUTH_SIZE];
	char *pcryptbuf = cryptbuf;

	tcgetattr(STDIN_FILENO, &ts);
	ots = ts;

	printf("Login:");
	fflush(stdout);
	gets(userbuf);

	/* 禁用终端回显 */
	ts.c_lflag &= ~ECHO;
	ts.c_lflag |= ECHONL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);

	printf("Password:");
	fflush(stdout);
	gets(passbuf);

	struct spwd *sp = getspnam(userbuf);
	if(sp == NULL) {
		printf("set sp error\n");
	}

	/* 验证用户名、密码的正确性 */
	pcryptbuf = crypt(passbuf, sp->sp_pwdp);
	printf("passbuf: %s\n", passbuf);
	printf("sp->sp_pwdp: %s\n", sp->sp_pwdp);
	printf("pcryptbuf: %s\n", pcryptbuf);
	if(!strcmp(sp->sp_pwdp, pcryptbuf)) {
		printf("correct\n");
	}
	else {
		printf("user or password error\n");
	}
	/* 恢复终端原来的属性 */
	tcsetattr(STDIN_FILENO, TCSANOW, &ots);
	return 0;
}
