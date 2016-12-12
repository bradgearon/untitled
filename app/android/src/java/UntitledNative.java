package com.wds.untitled;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.view.View;
import android.view.WindowManager;
import android.app.Activity;

public class UntitledNative {
  public static void setTheme(Activity activity) {
    activity.setTheme(R.style.Default_NoAnimation);
  }

  public static void sendToBack(Activity activity) {
    activity.setTheme(R.style.Translucent_NoAnimation);
    activity.moveTaskToBack(true);
    activity.overridePendingTransition(0, 0);
  }

  public static void bringToFront(Activity activity) {
    Intent intent = new Intent(activity, MyActivity.class);
    activity.startActivity(intent);
    activity.overridePendingTransition(0, 0);
    setTheme(activity);
  }

  public static void hideSystemUI(Activity activity) {
    View decorView = activity.getWindow().getDecorView();
        int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;
        if (Build.VERSION.SDK_INT < 16) {
                activity.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                    WindowManager.LayoutParams.FLAG_FULLSCREEN);
        } else {
            uiOptions |= View.SYSTEM_UI_FLAG_FULLSCREEN;
        }
        decorView.setSystemUiVisibility(uiOptions);
  }

  public static void init(Activity activity) {
    Intent intent = new Intent(activity, MyActivity.class);
    activity.startActivity(intent);
    activity.overridePendingTransition(0, 0);
  }
}
