hardware_modules := led gralloc hwcomposer audio nfc nfc-nci local_time power usbaudio audio_remote_submix
include $(call all-named-subdir-makefiles,$(hardware_modules))
