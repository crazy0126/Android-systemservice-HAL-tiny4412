/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//#include <cutils/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/led.h>


//定义ioctl命令号，参数是灯的编号
#define LED_TYPE 'L'
#define LED_ON	_IOW(LED_TYPE, 1, int)
#define LED_OFF	_IOW(LED_TYPE, 2, int)


struct led_control_device_t *sLedDevice = NULL;
int fd = -1;;
/* Close an opened led device instance */
static int led_device_close(hw_device_t *dev) {
    struct led_control_device_t * lcdt = (struct led_control_device_t *) dev;
    if(lcdt) {
	close(fd);
	free(lcdt);
    }
    return 0;
}

static int led_on(struct led_control_device_t *dev, int32_t num)
{
	ALOGI("LED Stub: set %d on .", num);
	if( fd == -1) {
		if((fd =open("/dev/led", O_RDWR))== -1)
		{
			ALOGE("LED open error: fd=%d",fd);
			return -1;
		} else 
			ALOGI(" LED open OK:  fd= %d",fd);
	}

	if(ioctl(fd,LED_ON, num)== -1){
		ALOGI("LED Stub: set_on failed! fd=%d", fd);
	};
	return 0;
}

static int led_off(struct led_control_device_t *dev, int32_t num)
{
	ALOGI("LED Stub: set %d off. ", num);
	if( fd == -1) {
		if((fd =open("/dev/led", O_RDWR))== -1)
		{
			ALOGE("LED open error: fd=%d",fd);
			return -1;
		} else 
			ALOGI(" LED open OK:  fd= %d",fd);
	}
	if(ioctl(fd,LED_OFF, num) ==-1){
		ALOGI("LED Stub: set_off failed! fd=%d", fd);
	};
	return 0;

}
/*
 * Generic device handling
 */
static int led_device_open(const hw_module_t* module, const char* name,
        hw_device_t** device) {

       struct led_control_device_t *dev = calloc(1, sizeof(struct led_control_device_t));

        dev->common.tag = HARDWARE_DEVICE_TAG;
        dev->common.version = 0;
        dev->common.module = module;
        dev->common.close = led_device_close;

        /* Example settings */
        dev->set_on = led_on;
	dev->set_off = led_off;

       // *device = (hw_device_t*) dev;
	*device = &dev->common;
	/*
	if((dev->fd = open("/dev/led", O_RDWR)) == -1) {
		ALOGE("LED Open Error!");
	} else {
		ALOGI("LED Open OK!");
	}
	*/

        return 0;

}


static struct hw_module_methods_t led_module_methods = {
    .open = led_device_open,
};

 struct led_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 0,
        .id = LED_HARDWARE_MODULE_ID,
        .name = "Sample LED HAL",
        .author = "The Stone Open Source Project",
        .methods = &led_module_methods,
    },
};
