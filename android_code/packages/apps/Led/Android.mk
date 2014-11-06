LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src) 

LOCAL_PACKAGE_NAME := LedServiceTest

#framework for LedManager; services for LedService
LOCAL_JAVA_LIBRARIES := services framework		
LOCAL_CERTIFICATE := platform
#LOCAL_PROGUARD_FLAG_FILES := proguard.flags

include $(BUILD_PACKAGE)

# Use the folloing include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))
