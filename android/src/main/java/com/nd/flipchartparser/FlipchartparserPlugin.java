package com.nd.flipchartparser;

import android.app.Activity;

import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import io.flutter.plugin.common.PluginRegistry.Registrar;

/** FlipchartparserPlugin */
public class FlipchartparserPlugin implements MethodCallHandler {

  // Used to load the 'native-lib' library on application startup.
  static {
    System.loadLibrary("native-lib");
  }

  /**
   * A native method that is implemented by the 'native-lib' native library,
   * which is packaged with this application.
   */
  public native String stringFromJNI();

  public native String openFlipchart(String flipchartPath,String uncompressPath);

  public native String loadPage(int pageNumber);

  public native void clear();

  public native void dispose();

  private static Activity mActivity;

  /** Plugin registration. */
  public static void registerWith(Registrar registrar) {
    final MethodChannel channel = new MethodChannel(registrar.messenger(), "flipchartparser");
    channel.setMethodCallHandler(new FlipchartparserPlugin());

    mActivity = (Activity)registrar.activeContext();

  }

  @Override
  public void onMethodCall(final MethodCall call, final Result result) {
    if (call.method.equals("getPlatformVersion")) {
//      String str = stringFromJNI();
//      Log.i("###1",str);
//      result.success("Android " + android.os.Build.VERSION.RELEASE);
    } else if(call.method.equals("openFlipchart")){

      String flipchartPath = call.argument("flipchartPath");
      String uncompressPath = call.argument("uncompressPath");
      String str = openFlipchart(flipchartPath,uncompressPath);
      result.success(str);
    } else if(call.method.equals("loadPage")){
//      new Thread(new Runnable() {
//        @Override
//        public void run() {
//          String uncompressPath = call.argument("uncompressPath");
//          int pageNumber = call.argument("pageNumber");
//          final String str = loadPage(pageNumber);
//          mActivity.runOnUiThread(new Runnable() {
//            @Override
//            public void run() {
//              result.success(str);
//            }
//          });
//
//        }
//      }).start();
      int pageNumber = call.argument("pageNumber");
      final String str = loadPage(pageNumber);
      result.success(str);
    } else if(call.method.equals("clear")){
      clear();
      result.success(null);
    } else if(call.method.equals("dispose")){
      dispose();
      result.success(null);
    } else {
      result.notImplemented();
    }
  }


}
