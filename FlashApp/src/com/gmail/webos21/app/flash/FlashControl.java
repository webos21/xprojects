package com.gmail.webos21.app.flash;

import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.util.Log;

@SuppressWarnings("deprecation")
public final class FlashControl {

	private static volatile FlashControl instance;

	private Camera camera;
	private Parameters params;

	private boolean flashOn;

	private FlashControl() {
	}

	public static FlashControl getInstance() {
		if (instance != null) {
			return instance;
		}
		synchronized (FlashControl.class) {
			if (instance != null) {
				return instance;
			}
			instance = new FlashControl();
		}
		return instance;
	}

	public static boolean hasFlash(Context context) {
		return context.getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA_FLASH);
	}

	public void init() {
		if (camera == null) {
			try {
				camera = Camera.open();
				params = camera.getParameters();
			} catch (RuntimeException e) {
				Log.e("Camera Error. Failed to Open. Error: ", e.getMessage());
			}
		}
	}

	public void destroy() {
		if (camera != null) {
			turnOff();
			camera.release();
			camera = null;
		}
	}

	public boolean isFlashOn() {
		return flashOn;
	}

	public void resetCamera() {
		if (camera == null) {
			try {
				camera = Camera.open();
				params = camera.getParameters();
			} catch (RuntimeException e) {
				Log.e("Camera Error. Failed to Open. Error: ", e.getMessage());
			}
		}
	}

	public void turnOn() {
		if (camera == null || params == null) {
			return;
		}
		if (!flashOn) {
			params.setFlashMode(Parameters.FLASH_MODE_TORCH);
			camera.setParameters(params);
			camera.startPreview();
			flashOn = true;
		}
	}

	public void turnOff() {
		if (camera == null || params == null) {
			return;
		}
		if (flashOn) {
			params.setFlashMode(Parameters.FLASH_MODE_OFF);
			camera.setParameters(params);
			camera.stopPreview();
			flashOn = false;
		}
	}
}
