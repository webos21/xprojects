package com.github.webos21.ioio.hello;

import ioio.lib.api.DigitalOutput;
import ioio.lib.api.PwmOutput;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.BaseIOIOLooper;
import ioio.lib.util.IOIOLooper;
import ioio.lib.util.pc.IOIOConsoleApp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MoveMotor extends IOIOConsoleApp {

	private boolean motorLeft = false;
	private boolean motorRight = false;
	private float speed = 0;

	public static void main(String[] args) throws Exception {
		new MoveMotor().go(args);
	}

	@Override
	protected void run(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean abort = false;
		String line;
		while (!abort && (line = reader.readLine()) != null) {
			if (line.equals("a")) { // left
				motorLeft = true;
				motorRight = true;
				speed = 0.4F;
			} else if (line.equals("d")) { // right
				motorLeft = false;
				motorRight = false;
				speed = 0.4F;
			} else if (line.equals("w")) { // forward
				motorLeft = false;
				motorRight = true;
				speed = 0.4F;
			} else if (line.equals("s")) { // backward
				motorLeft = true;
				motorRight = false;
				speed = 0.4F;
			} else if (line.equals("x")) { // stop
				speed = 0F;
			} else if (line.equals("q")) { // quit
				abort = true;
			} else {
				System.out.println("Unknown input. a=left, d=right, w=forward, s=backward, x=stop.");
			}
		}
	}

	@Override
	public IOIOLooper createIOIOLooper(String connectionType, Object extra) {
		return new MotorLooper();
	}

	private class MotorLooper extends BaseIOIOLooper {

		// Declare PIN
		private DigitalOutput PinDO0; // LED STAT

		// Motor DC : Right
		private DigitalOutput PinDIO36; // L293D In 3
		private DigitalOutput PinDIO37; // L293D In 4
		private PwmOutput PinPWM38; // L293D Enable 2

		// Motor DC : Left
		private DigitalOutput PinDIO40; // L293D In 2
		private DigitalOutput PinDIO41; // L293D In 1
		private PwmOutput PinPWM39; // L293D Enable 1

		@Override
		protected void setup() throws ConnectionLostException, InterruptedException {
			// super.setup();
			// Assign PIN
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

		}

		@Override
		public void loop() throws ConnectionLostException, InterruptedException {

			PinDO0.write((speed == 0F));

			PinPWM39.setDutyCycle(speed);
			PinDIO41.write(motorLeft);
			PinDIO40.write(!motorLeft);

			PinPWM38.setDutyCycle(speed);
			PinDIO37.write(motorRight);
			PinDIO36.write(!motorRight);

			Thread.sleep(10);
		} // End Loop

	}
}
