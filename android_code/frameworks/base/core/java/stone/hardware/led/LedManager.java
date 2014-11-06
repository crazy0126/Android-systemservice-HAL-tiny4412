package stone.hardware.led;
import android.os.RemoteException;
import android.util.Log;
import stone.hardware.led.ILedService;
/**
 * Wrapper class for LedService;
 */

public class LedManager
{
	private static final String TAG = "LedManager";
	private final ILedService mLedService;

	public LedManager(ILedService service) {
		mLedService = service;
	}
	
	public boolean ledOn(int num) {
		boolean result = false;
		try {
			result = mLedService.setOn(num);
		}catch (RemoteException e) {
			Log.e(TAG, "RemoteException in LedManager.ledOn: ", e);
		}
		return result;
	}
	
	public boolean ledOff(int num) {

		boolean result = false;
		try {
			result = mLedService.setOff(num);
		} catch (RemoteException e) {
			Log.e(TAG, "RemoteException in LedManager.ledOff: ", e);
		}
		return result;
	}


}
