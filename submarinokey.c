#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <ncurses.h>

#include "subdriver.h"

#define DEVICE_NAME "/dev/submarino"

int main(int argc, char **argv) {
	int fp, ret;

	fp = open(DEVICE_NAME, O_RDWR);

	if (fp < 0) {
		perror("Não foi possível acessar o dispositivo!");
	}
	
	initscr();
    cbreak();
    noecho();

	char key;
	while(key != 'q') {
		key = getch();

		if (key == '\033') {
			getch();
			switch(getch()) {
			case 'A':
				ret = ioctl(fp, IOCTL_UP);
				break;
			case 'B':
				ret = ioctl(fp, IOCTL_DOWN);
				break;
			case 'C':
				ret = ioctl(fp, IOCTL_RIGHT);
				break;
			case 'D':
				ret = ioctl(fp, IOCTL_LEFT);
				break;
			}
		}
	}
	endwin();

	return 0;
}