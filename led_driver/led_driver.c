/************************
 * Led Driver
 * Author: ZJG
 * Date: 2015-01-02
 ************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>
#include <linux/proc_fs.h>

//define led num
#define LED_NUM		4

//define led gpio num
#define LED0 EXYNOS4X12_GPM4(0)
#define LED1 EXYNOS4X12_GPM4(1)
#define LED2 EXYNOS4X12_GPM4(2)
#define LED3 EXYNOS4X12_GPM4(3)

//define ioctl cmd, param is the led num.
#define LED_TYPE 'L'
#define LED_ON	_IOW(LED_TYPE, 1, int)
#define LED_OFF	_IOW(LED_TYPE, 2, int)

static int led_gpios[LED_NUM] = {
	LED0, LED1, LED2, LED3,
};


//file_operations

static long
led_ioctl(struct file *filp, unsigned int req, unsigned long arg)
{
	if (arg >= LED_NUM) {
		printk("Only support %d LEDS\n", LED_NUM);
		return -1;
	}
	switch (req) {
	case LED_ON:
		gpio_set_value(led_gpios[arg], 0);
		break;
	case LED_OFF:
		gpio_set_value(led_gpios[arg], 1);
		break;
	default:
		printk("Not support ioctl 0x%x\n", req);
		return -1;
	}

	return 0;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = led_ioctl,
};

static struct miscdevice led_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "led",
	.fops = &led_fops,
};

static int __init my_init(void)
{
	int i, j, ret;

	//1.Initilize the four leds.
	for (i=0; i<LED_NUM; i++) {
		ret = gpio_request(led_gpios[i], "myled");
		if (ret) {
			printk("Cannot get gpio %d\n", led_gpios[i]);
			goto err;
		}
		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i], 1);
	}

	//2.misc_register
	ret = misc_register(&led_misc);
	if (ret) {
		printk("Cannot register misc device for led\n");
		goto err;
	}


	return 0;
err:
	for (j=0; j<i; j++)
		gpio_free(led_gpios[j]);
	return -1;
}

static void __exit my_exit(void)
{
	int i;
	remove_proc_entry("led_misc", NULL);
	misc_deregister(&led_misc);
	for (i=0; i<LED_NUM; i++)
		gpio_free(led_gpios[i]);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

