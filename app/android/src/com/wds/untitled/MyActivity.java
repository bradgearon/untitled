package com.wds.untitled;

import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;

import org.qtproject.qt5.android.bindings.QtActivity;

public class MyActivity extends QtActivity {
  public MyActivity() {
    super();
    QT_ANDROID_DEFAULT_THEME = "Theme_Translucent_NoTitleBar_Fullscreen";
  }

  @Override
  public void onCreate(Bundle savedInstanceState) {
    UntitledNative.hideSystemUI(this);
    super.onCreate(savedInstanceState);
  }

  @Override
  public boolean onKeyUp(int keyCode, KeyEvent event) {
    return keyCode == KeyEvent.KEYCODE_BACK || super.onKeyUp(keyCode, event);
  }

  @Override
  public void onBackPressed() {
    Log.d("com.wds.untitled", "on back pressed");
  }
}
