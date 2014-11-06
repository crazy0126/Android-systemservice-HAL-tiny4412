#include <fcntl.h>
#include <errno.h>
#include <hardware/hardware.h>
#include <cutils/log.h>
#include <cutils/atomic.h>


/******************************************************/
struct led_module_t {
	struct hw_module_t common;
};
struct led_control_device_t {
	struct hw_device_t common;
	/* attributes go here */
	int fd;
	
	/* Supported control APIs go here */
		
	int (*set_on)(struct led_control_device_t *dev, int32_t num);
	int (*set_off)(struct led_control_device_t *dev, int32_t num);


};

#define LED_HARDWARE_MODULE_ID "led"
