package com.wds.untitled;

import android.os.Bundle;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.content.pm.ActivityInfo;
import android.view.WindowManager;

public class MyActivity extends QtActivity
{
    public MyActivity()
    {
        super();
        QT_ANDROID_DEFAULT_THEME = "Theme_Translucent_NoTitleBar_Fullscreen";
    }

  @Override
      public void onCreate(Bundle savedInstanceState) {
          super.onCreate(savedInstanceState);
          UntitledNative.hideSystemUI(this);
      }

}
