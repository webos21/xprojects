package com.gmail.webos21.motorapp;

import ioio.lib.api.DigitalOutput;
import ioio.lib.api.PwmOutput;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.BaseIOIOLooper;
import ioio.lib.util.IOIOLooper;
import ioio.lib.util.android.IOIOActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.ToggleButton;

public class MainActivity extends IOIOActivity {

	private ToggleButton toggleButtonLedSTAT;
	protected Button buttonLeft;
	protected Button buttonRight;
	protected Button buttonUp;
	protected Button buttonDown;

	private boolean motorLeft = false;
	private boolean motorRight = false;
	private float speed = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		toggleButtonLedSTAT = (ToggleButton) findViewById(R.id.toggleButtonLedSTAT);

		buttonLeft = (Button) findViewById((R.id.buttonLeft));
		buttonRight = (Button) findViewById((R.id.buttonRight));
		buttonUp = (Button) findViewById((R.id.buttonUp));
		buttonDown = (Button) findViewById((R.id.buttonDown));

		enableUi(false);

		buttonLeft.setOnTouchListener(new View.OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				v.performClick();
				if ((event.getAction() == MotionEvent.ACTION_MOVE) || (event.getActionMasked() != MotionEvent.ACTION_UP)) {
					motorLeft = true;
					motorRight = true;
					speed = 0.7F;
				} else {
					speed = 0F;
				}
				return false;
			}
		});

		buttonRight.setOnTouchListener(new View.OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				v.performClick();
				if ((event.getAction() == MotionEvent.ACTION_MOVE) || (event.getActionMasked() != MotionEvent.ACTION_UP)) {
					motorLeft = false;
					motorRight = false;
					speed = 0.7F;
				} else {
					speed = 0;
				}
				return false;
			}
		});

		buttonUp.setOnTouchListener(new View.OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				v.performClick();
				if ((event.getAction() == MotionEvent.ACTION_MOVE) || (event.getActionMasked() != MotionEvent.ACTION_UP)) {
					motorLeft = false;
					motorRight = true;
					speed = 1F;
				} else {
					speed = 0F;
				}
				return false;
			}
		});

		buttonDown.setOnTouchListener(new View.OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				v.performClick();
				if ((event.getAction() == MotionEvent.ACTION_MOVE) || (event.getActionMasked() != MotionEvent.ACTION_UP)) {
					motorLeft = true;
					motorRight = false;
					speed = 0.5F;
				} else {
					speed = 0;
				}
				return false;
			}
		});

	}

	private void enableUi(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				toggleButtonLedSTAT.setEnabled(enable); // the toggleButton is disable
				toggleButtonLedSTAT.setChecked(enable); // switch on the toggleButton
				if (enable) {
					Toast.makeText(MainActivity.this, getString(R.string.IOIOConnected), Toast.LENGTH_LONG).show();
				} else {
					Toast.makeText(MainActivity.this, getString(R.string.IOIODisconnected), Toast.LENGTH_LONG).show();
				}
			}
		});
	}

	@Override
	protected IOIOLooper createIOIOLooper() {
		return new Looper();
	}

	class Looper extends BaseIOIOLooper {

		// Declare PIN
		private DigitalOutput PinDO0; // LED STAT

		// Motor DC : Right
		private DigitalOutput PinDIO36; // L293D In 1
		private DigitalOutput PinDIO37; // L293D In 2
		private PwmOutput PinPWM38; // L293D Enable 1

		// Motor DC : Left
		private DigitalOutput PinDIO40; // L293D In 3
		private DigitalOutput PinDIO41; // L293D In 4
		private PwmOutput PinPWM39; // L293D Enable 2

		@Override
		protected void setup() throws ConnectionLostException, InterruptedException {

			// LED STAT
			PinDO0 = ioio_.openDigitalOutput(0, true);

			// Motor DC : Right
			PinDIO36 = ioio_.openDigitalOutput(36);
			PinDIO37 = ioio_.openDigitalOutput(37);
			PinPWM38 = ioio_.openPwmOutput(38, 100);

			// Motor DC : Left
			PinDIO40 = ioio_.openDigitalOutput(40);
			PinDIO41 = ioio_.openDigitalOutput(41);
			PinPWM39 = ioio_.openPwmOutput(39, 100);

			enableUi(true); // Start IOIO
		}

		@Override
		public void loop() throws ConnectionLostException, InterruptedException {
			// super.loop();

			PinDO0.write(!toggleButtonLedSTAT.isChecked());

			PinPWM39.setDutyCycle(speed);
			PinDIO41.write(motorLeft);
			PinDIO40.write(!motorLeft);

			PinPWM38.setDutyCycle(speed);
			PinDIO37.write(motorRight);
			PinDIO36.write(!motorRight);

			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}

		@Override
		public void disconnected() {
			// super.disconnected();
			enableUi(false);
			toggleButtonLedSTAT.setEnabled(false); // the toggleButton is disable
			toggleButtonLedSTAT.setChecked(false); // switch off the toggleButton
			Toast.makeText(MainActivity.this, getString(R.string.IOIODisconnected), Toast.LENGTH_LONG).show();

		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.menu_main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();

		// noinspection SimplifiableIfStatement
		if (id == R.id.action_settings) {
			return true;
		}

		return super.onOptionsItemSelected(item);
	} // End onOptionsItemSelected
}
