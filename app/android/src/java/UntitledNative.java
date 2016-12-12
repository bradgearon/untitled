package com.wds.untitled;

import android.content.Intent;
import android.os.Build;
import android.view.View;
import android.app.Activity;

public class UntitledNative {

  public static void setTheme(Activity activity) {
    activity.overridePendingTransition(0, 0);
    activity.setTheme(R.style.Default_NoAnimation);
    activity.overridePendingTransition(0, 0);
  }

  public static void sendToBack(Activity activity) {
    activity.overridePendingTransition(0, 0);
    activity.setTheme(R.style.Translucent_NoAnimation);
    activity.moveTaskToBack(true);
    activity.overridePendingTransition(0, 0);
  }

  public static void bringToFront(Activity activity) {
    activity.overridePendingTransition(0, 0);
    activity.setTheme(R.style.Default_NoAnimation);
    Intent intent = activity.getIntent();
    activity.startActivity(intent);
    activity.overridePendingTransition(0, 0);
  }

}
