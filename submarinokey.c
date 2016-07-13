#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>

#include "subdriver.h"

int main(int argc, char **argv) {
	int fp, ret;

	initscr();
    cbreak();
    noecho();
    addstr("Pressione Q para sair\n\nComandos:\n");

	char key;
	while(key != 'q') {
		key = getch();

		if (key == '\033') {
			getch();
			key = getch();

			fp = open(DEVICE_PATH, O_RDWR);
			if (fp < 0) {
				perror("Não foi possível acessar o dispositivo!");
			}

			switch (key) {
			case 65:
				addstr("^ ");
				break;
			case 68:
				addstr("< ");
				break;
			case 66:
				addstr("_ ");
				break;
			case 67:
				addstr("> ");
				break;
			}

			
			ret = ioctl(fp, IOCTL_SET_KEY, &key);

			close(fp);
		}
	}
	endwin();

	return 0;
}