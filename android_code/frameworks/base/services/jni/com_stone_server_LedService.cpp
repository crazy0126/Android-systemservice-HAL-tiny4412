
/* //device/libs/android_runtime/android_server_AlarmManagerService.cpp
**
** Copyright 2006, The Stone Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "LedService"


#include "JNIHelp.h"
#include "jni.h"
#include <utils/Log.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hardware/led.h>

namespace android {
struct led_control_device_t *sLedDevice = NULL;

static jboolean stone_setOn(JNIEnv *env, jobject thiz, jint num)
{




	ALOGI("LedService JNI: stone_setOn() is invoked.");
	if(sLedDevice == NULL) {
		//LOGI("LedService JNI: sLedDevice was not fetched correctly.");	//error
		ALOGI("LedService JNI: sLedDevice was not fetched correctly.");
		return -1;
	}else {
	
		return sLedDevice->set_on(sLedDevice, num);
	}

}
static jboolean stone_setOff(JNIEnv *env, jobject thiz, jint num)
{

	//LOGI("LedService JNI: stone_setOff() is invoked.");		//error
	ALOGI("LedService JNI: stone_setOff() is invoked.");
	if(sLedDevice == NULL) {
		ALOGI("LedService JNI: sLedDevice was not fetched correctly.");
		return -1;
	}else {
	
		return sLedDevice->set_off(sLedDevice, num);
	}

}

/** helper APIs */
static inline int led_control_open(const struct hw_module_t *module, struct led_control_device_t** device) {
	return module->methods->open(module,
	 LED_HARDWARE_MODULE_ID, (struct hw_device_t **)device);

}

static jboolean stone_init(JNIEnv *env, jclass clazz)
{
	led_module_t *module;
	if (hw_get_module(LED_HARDWARE_MODULE_ID, (const hw_module_t **)&module) == 0) {
		ALOGI("LedService JNI: LED Stub found.");
		if(led_control_open(&module->common, &sLedDevice) == 0) {
			ALOGI("LedService JNI: Got Stub operations.");
			return 0;
		}
		
	}
	ALOGE("LedService JNI: LED Stub found  failed.");
	return -1;
}


//----------------------------------------------------------------------------

static JNINativeMethod sMethods[] = {
     /* name, signature, funcPtr */
	{"_init", "()Z", (void*)stone_init},
	{"_set_on", "(I)Z", (void*)stone_setOn},
	{"_set_off", "(I)Z", (void*)stone_setOff},
};

int register_stone_server_LedService(JNIEnv* env)
{
    return jniRegisterNativeMethods(env, "com/stone/server/LedService",
                                    sMethods, NELEM(sMethods));
}
} /* namespace android */

