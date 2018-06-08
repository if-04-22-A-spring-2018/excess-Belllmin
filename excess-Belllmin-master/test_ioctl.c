#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void print_page(char buffer[]);
int main(int argc,char *argv[])
{
	char buffer[100];

	FILE *fd = fopen(argv[0], "r");
	if(fd != NULL)
	{
		fgets(buffer, 100, fd);
	}

	int n = 0;

	while((n = read(0, buffer, sizeof(buffer))) != 0)
	{
		printf("Char: %c\n", n);
		fflush(stdout);
		write(1, buffer, n);
	}

	print_page(buffer);

	struct winsize ws;

	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}
	printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
	ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);
	return 0;
}

void print_page(char buffer[])
{
	for(int i = 0; i < 100; i++)
	{
		printf("%s ", buffer[i]);
	}
	printf("\n");
}
