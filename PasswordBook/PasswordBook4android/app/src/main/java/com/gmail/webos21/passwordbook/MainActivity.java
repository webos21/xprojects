package com.gmail.webos21.passwordbook;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    public static final int LOGIN_ACTION = 1;

    private boolean loginFlag;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onStart() {
        super.onStart();
        if (!loginFlag) {
            Intent i = new Intent(this, AuthActivity.class);
            startActivityForResult(i, LOGIN_ACTION);
        }
    }

    @Override
    protected void onStop() {
        loginFlag = false;
        super.onStop();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == LOGIN_ACTION) {
            if (resultCode == RESULT_OK) {
                loginFlag = true;
            } else {
                finish();
            }
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

}
