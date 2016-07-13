#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "../subdriver.h"
#include "SubmarinoScreen.h"

JNIEXPORT jint JNICALL
Java_SubmarinoScreen_keyListner(JNIEnv *env, jclass obj) {
	int fp;
	char key = 0;

	while (!key) {
		fp = open(DEVICE_PATH, O_RDONLY);
		if (fp < 0) {
			perror("Nao foi possivel acessar o dispositivo!\n");
			return -1;
		}

		ioctl(fp, IOCTL_GET_KEY, &key);
		close(fp);
		usleep(10);
	}

	return key;
}