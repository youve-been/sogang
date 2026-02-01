#ifndef __DEV_HEADER_H__

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/string.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/version.h>

#define DEV_MAJOR           242
#define DEV_NAME            "dev_driver"

#define LED_ADDRESS         0x08000016
#define SWITCH_ADDRESS      0x08000050
#define FND_ADDRESS         0x08000004
#define N_SWITCH            9

#define START               _IO(DEV_MAJOR, 0)
#define READ_SW             _IOR(DEV_MAJOR, 1, unsigned char *)
#define LOSE_LIFE           _IOW(DEV_MAJOR, 2, unsigned char *)
#define END                 _IOW(DEV_MAJOR, 3, int *)

#endif