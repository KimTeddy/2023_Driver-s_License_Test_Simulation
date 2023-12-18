#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <linux/input.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "button.h"
#include <linux/fb.h>

