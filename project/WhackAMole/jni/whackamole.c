#include <jni.h>
#include "android/log.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>

#define LOGV(...)   __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGE(...)   __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define LOG_TAG "MyTag"
#define DEV_MAJOR 242

#define START               _IO(DEV_MAJOR, 0)
#define READ_SW             _IOR(DEV_MAJOR, 1, unsigned char *)
#define LOSE_LIFE           _IOW(DEV_MAJOR, 2, unsigned char *)
#define END                 _IOW(DEV_MAJOR, 3, int *)

int fd;

jint JNICALL Java_com_example_whackamole_Start_driverOpen (JNIEnv *env, jobject this)
{
    fd = open("/dev/dev_driver", O_RDWR);
    if (fd == -1) {
        LOGE("Failed to open device driver: %s", strerror(errno));
        return -1;
    }
    LOGV("device driver open : %d", fd);

    ioctl(fd, START);
	LOGV("IO init!");

}

void JNICALL Java_com_example_whackamole_WhackAMole_driverClose (JNIEnv *env, jobject this)
{
	int res = close(fd);
	if (res == -1) {
		LOGE("Failed to close fd %d: %s", fd, strerror(errno));
		return;
	}
	LOGV("device driver close : %d", res);
}

void JNICALL Java_com_example_whackamole_GameOver_driverClose (JNIEnv *env, jobject this)
{
	int res = close(fd);
	if (res == -1) {
		LOGE("Failed to close fd %d: %s", fd, strerror(errno));
		return;
	}
	LOGV("device driver close : %d", res);
}

void JNICALL Java_com_example_whackamole_GameOver_gameOver (JNIEnv *env, jobject this, jint score)
{
	int s = score;
	ioctl(fd, END, &s);
	LOGV("GAME OVER!");
}

jint JNICALL Java_com_example_whackamole_WhackAMole_readSwitchInput (JNIEnv *env, jobject this, jint curr)
{
	unsigned char pressed;
	ioctl(fd, READ_SW, &pressed);

	LOGV("current = %d, pressed : %d", curr, pressed);
	if (pressed == 255)
		return -1;
	else
		return curr == pressed;
}

void JNICALL Java_com_example_whackamole_WhackAMole_loseLife (JNIEnv *env, jobject this, jint lives)
{
	unsigned char l = lives;
	ioctl(fd, LOSE_LIFE, &l);
}
