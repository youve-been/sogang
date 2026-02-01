#include "dev_header.h"

int dev_open(struct inode *inode, struct file *file);
static long dev_ioctl(struct file *, unsigned int , unsigned long);
int dev_release(struct inode *inode, struct file *file);


static int dev_usage = 0;
static unsigned char *led_addr;
static unsigned char *switch_addr;
static unsigned char *fnd_addr;

struct file_operations dev_fops =
{
	.open				=	dev_open,	
	.unlocked_ioctl 	= 	dev_ioctl,
	.release			=	dev_release,
};

int dev_open(struct inode *inode, struct file *file) {
	printk("dev_open\n");
	if (dev_usage != 0) {
		return -EBUSY;
	}
	dev_usage = 1;
	return 0;
}

int dev_release(struct inode *inode, struct file *file) {

	outw(0, (unsigned int)led_addr);
	outw(0, (unsigned int)fnd_addr);

	printk("dev_release\n");
	dev_usage = 0;
	return 0;
}

void led_write(unsigned char num) 
{
	unsigned char value;
	unsigned short _s_value;
	int i;

	value = (1 << 8) - 1;
	
	i = 7;
	while (i >= num) {
		value -= 1 << i;
		i--;
	}

    _s_value = (unsigned short)value;
    outw(_s_value, (unsigned int)led_addr);
}

void read_switch(unsigned char *buff)
{
	int i = 0;
	unsigned short int _s_value;

	while (i<N_SWITCH) {
		_s_value = inw((unsigned int)switch_addr+i*2);
        buff[i] = _s_value &0xFF;
		i++;
    }
}

void write_score(int score)
{
	int i = 3;
	unsigned char value[4];
	unsigned short int value_short = 0;
	while (i >= 0) {
		value[i] = score % 10;
		score /= 10;
		i--;
	}

    value_short = value[0] << 12 | value[1] << 8 |value[2] << 4 |value[3];
    outw(value_short,(unsigned int)fnd_addr);
}

static long dev_ioctl(struct file *inode, unsigned int cmd, unsigned long arg)
{
	unsigned char buff[N_SWITCH];
	unsigned char lives, pressed = -1;
	int i, score;

	switch (cmd) {
		case START:
			outw((1<<8)-1, (unsigned int)led_addr);
			outw(0, (unsigned int)fnd_addr);
			printk("ioctl start working!\n");
			break;
		case READ_SW:
			read_switch(buff);
			i = 0;
			while (i < N_SWITCH) {
				if (buff[i] != 0)
					pressed = i;
				i++;
			}
			printk("%d pressed!\n", pressed);
			if (copy_to_user((unsigned char *)arg, &pressed, sizeof(unsigned char))) {
                return -EACCES;
            }
			break;
		case LOSE_LIFE:
			printk("ioctl lose life working!\n");
			if (copy_from_user(&lives, (const unsigned char *)arg, sizeof(unsigned char))) {
				return -EFAULT;
			}
			printk("%d lives left!\n", lives);
			led_write(lives);
			break;
		case END:
			if (copy_from_user(&score, (const int *)arg, sizeof(int))) {
				return -EFAULT;
			}
			outw(0, (unsigned int)led_addr);
			write_score(score);
			printk("ioctl end working!\n");
			printk("score : %d\n", score);
			break;
	}

	return 0;
}

int __init dev_init(void)
{
	int result;

	printk("dev_init\n");

	result = register_chrdev(DEV_MAJOR, DEV_NAME, &dev_fops);
	if(result <0) {
		printk( "error %d\n",result);
		return result;
	}
	led_addr = ioremap(LED_ADDRESS, 0x1);
	switch_addr = ioremap(SWITCH_ADDRESS, 0x18);
	fnd_addr = ioremap(FND_ADDRESS, 0x4);

    printk( "dev_file : /dev/%s , major : %d\n",DEV_NAME, DEV_MAJOR);
	return 0;
}

void __exit dev_exit(void) 
{
    printk("dev_exit\n");
	dev_usage = 0;
	iounmap(led_addr);
    iounmap(switch_addr);
    iounmap(fnd_addr);
	unregister_chrdev(DEV_MAJOR, DEV_NAME);
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("author");
