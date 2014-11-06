package com.stone.server;

import stone.hardware.led.ILedService;
import android.content.Context;
import android.os.RemoteException;
import android.util.Log;



public final class LedService extends ILedService.Stub {
	
	private static final String TAG = "LedService";
	//加载动态库
	static {
		System.load("/system/lib/libandroid_servers.so");	//System.load System.loadLibrary
	}
	public LedService(Context context) {
		Log.i(TAG, "LedService Constructor");
		_init();
	}
	public boolean setOn(int num) {
		Log.i(TAG, "Led" + num + " On");
		_set_on(num);
		return true;
	}
	
	public boolean setOff(int num) {
		Log.i(TAG, "Led" + num + "Off");
		_set_off(num);
		return true;
	}

	//本地方法声明
	native private static boolean _init();
	native private static boolean _set_on(int num);
	native private static boolean _set_off(int num);
	
}





