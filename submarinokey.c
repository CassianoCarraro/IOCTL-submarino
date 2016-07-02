#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "subdriver.h"

#define DEVICE_NAME "/dev/submarino"

int main(int argc, char **argv) {
	int fp, ret;

	fp = open(DEVICE_NAME, O_RDWR);

	if (fp < 0) {
		perror("Não foi possível acessar o dispositivo!");
	}

	int key;
	int a = 10;

	while(a > 0) {
		scanf("%d", &key);
		ret = ioctl(fp, IOCTL_UP);
		printf("%c\n", key);
		a--;
	}
}