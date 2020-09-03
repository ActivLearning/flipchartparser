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
  public native boolean config(String tempPath,boolean logEnabled);
  public native String loadPage(int handle,int pageNumber);
  public native int newInstance();
  public native String openFlipchart(int handle,String flipchartPath);


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
      result.success("Android " + android.os.Build.VERSION.RELEASE);
    } else if(call.method.equals("openFlipchart")){
      String flipchartPath = call.argument("flipchartPath");
      int handle = call.argument("handle");
      String str = openFlipchart(handle,flipchartPath);
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
      int handle = call.argument("handle");
      final String str = loadPage(handle,pageNumber);
      result.success(str);
    } else if(call.method.equals("clear")){
      result.success(null);
    } else if(call.method.equals("dispose")){
      result.success(null);
    } else if(call.method.equals("config")){
      String tempPath = call.argument("tempPath");
      boolean logEnabled = call.argument("logEnabled");
      boolean success = config(tempPath,logEnabled);
      result.success(success);
    }else if(call.method.equals("newInstance")){
      int handle = newInstance();
      result.success(handle);
    }
    else {
      result.notImplemented();
    }
  }


}
