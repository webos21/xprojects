package com.gmail.webos21.app.flash;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class MainActivity extends Activity {

	private ImageButton btnSwitch;

	private FlashControl flashCtrl;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		// flash switch button
		btnSwitch = (ImageButton) findViewById(R.id.btnSwitch);

		if (!FlashControl.hasFlash(MainActivity.this)) {
			// device doesn't support flash
			// Show alert message and close the application
			AlertDialog alert = new AlertDialog.Builder(MainActivity.this).create();
			alert.setTitle("Error");
			alert.setMessage("Sorry, your device doesn't support flash light!");
			alert.setButton(DialogInterface.BUTTON_POSITIVE, "OK", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					// closing the application
					finish();
				}
			});
			alert.show();
			return;
		}

		flashCtrl = FlashControl.getInstance();
		flashCtrl.init();

		SoundControl.playSound(MainActivity.this, R.raw.light_switch_on);
		flashCtrl.turnOn();

		/*
		 * Switch button click event to toggle flash on/off
		 */
		btnSwitch.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				if (flashCtrl.isFlashOn()) {
					SoundControl.playSound(MainActivity.this, R.raw.light_switch_off);
					flashCtrl.turnOff();
					toggleButtonImage(false);
				} else {
					SoundControl.playSound(MainActivity.this, R.raw.light_switch_on);
					flashCtrl.turnOn();
					toggleButtonImage(true);
				}
			}
		});
	}

	/*
	 * Toggle switch button images changing image states to on / off
	 */
	private void toggleButtonImage(boolean flashOn) {
		if (flashOn) {
			btnSwitch.setImageResource(R.drawable.btn_switch_on);
		} else {
			btnSwitch.setImageResource(R.drawable.btn_switch_off);
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	@Override
	protected void onPause() {
		super.onPause();

		SoundControl.playSound(MainActivity.this, R.raw.light_switch_off);
		flashCtrl.turnOff();
		toggleButtonImage(false);
	}

	@Override
	protected void onRestart() {
		super.onRestart();
	}

	@Override
	protected void onResume() {
		super.onResume();

		// on resume turn on the flash
		if (FlashControl.hasFlash(MainActivity.this)) {
			flashCtrl.init();
		}
	}

	@Override
	protected void onStart() {
		super.onStart();

		flashCtrl.init();
	}

	@Override
	protected void onStop() {
		super.onStop();

		if (flashCtrl != null) {
			flashCtrl.destroy();
		}
	}

}
