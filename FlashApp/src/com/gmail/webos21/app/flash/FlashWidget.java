package com.gmail.webos21.app.flash;

import android.app.PendingIntent;
import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.RemoteViews;

public class FlashWidget extends AppWidgetProvider {

	private static final String TAG = FlashWidget.class.getSimpleName();

	public static String ACTION_TOGGLE = "com.gmail.webos21.app.flash.widget.ACTION_TOGGLE";

	private FlashControl flashCtrl;

	@Override
	public void onUpdate(Context context, AppWidgetManager appWidgetManager, int[] appWidgetIds) {

		if (flashCtrl == null) {
			flashCtrl = FlashControl.getInstance();
			flashCtrl.init();
		}

		int imgId = (flashCtrl.isFlashOn()) ? R.drawable.btn_switch_on : R.drawable.btn_switch_off;

		// Perform this loop procedure for each App Widget that belongs to this provider
		for (int appWidgetId : appWidgetIds) {
			// Create an Self-Pending-Intent
			Intent intent = new Intent(context, FlashWidget.class);
			intent.setAction(ACTION_TOGGLE);
			PendingIntent pendingIntent = PendingIntent.getBroadcast(context, 0, intent, 0);

			// Get the button view and Attach an on-click listener to the button
			RemoteViews views = new RemoteViews(context.getPackageName(), R.layout.lo_widget);
			views.setImageViewResource(R.id.btnWidgetSwitch, imgId);
			views.setOnClickPendingIntent(R.id.btnWidgetSwitch, pendingIntent);

			// Tell the AppWidgetManager to perform an update on the current app widget
			appWidgetManager.updateAppWidget(appWidgetId, views);
		}
	}

	@Override
	public void onReceive(Context context, Intent intent) {
		super.onReceive(context, intent);

		String action = intent.getAction();
		Log.i(TAG, "!!!!!!! Action = " + action);

		if (ACTION_TOGGLE.equals(action)) {
			toggleFlash(context);
			onUpdate(context);
		} else if (AppWidgetManager.ACTION_APPWIDGET_DISABLED.equals(action)) {
			if (flashCtrl != null) {
				flashCtrl.destroy();
				flashCtrl = null;
			}
		}
	}

	private void toggleFlash(Context context) {
		if (flashCtrl == null && FlashControl.hasFlash(context)) {
			flashCtrl = FlashControl.getInstance();
			flashCtrl.init();
		}

		if (flashCtrl.isFlashOn()) {
			SoundControl.playSound(context, R.raw.light_switch_off);
			flashCtrl.turnOff();
		} else {
			SoundControl.playSound(context, R.raw.light_switch_on);
			flashCtrl.turnOn();
		}
	}

	private void onUpdate(Context context) {
		AppWidgetManager appWidgetManager = AppWidgetManager.getInstance(context);

		// Uses getClass().getName() rather than MyWidget.class.getName() for
		// portability into any App Widget Provider Class
		ComponentName thisAppWidgetComponentName = new ComponentName(context.getPackageName(), getClass().getName());
		int[] appWidgetIds = appWidgetManager.getAppWidgetIds(thisAppWidgetComponentName);
		onUpdate(context, appWidgetManager, appWidgetIds);
	}

}
