package com.gmail.webos21.app.flash;

import android.content.Context;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;

public final class SoundControl {

	private static final boolean USE_SOUND = false;

	private SoundControl() {
	}

	public static void playSound(Context context, int soundId) {
		if (!USE_SOUND) {
			return;
		}

		MediaPlayer mp = MediaPlayer.create(context, soundId);
		mp.setOnCompletionListener(new OnCompletionListener() {
			@Override
			public void onCompletion(MediaPlayer mp) {
				mp.release();
			}
		});
		mp.start();
	}

}
