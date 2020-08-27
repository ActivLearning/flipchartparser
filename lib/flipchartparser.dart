import 'dart:async';

import 'package:flutter/services.dart';

class Flipchartparser {
  static const MethodChannel _channel = const MethodChannel('flipchartparser');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  static Future<String> openFlipchart(
      String flipchartPath, String uncompressPath) async {
    final String result = await _channel.invokeMethod(
        'openFlipchart', <String, dynamic>{
      'flipchartPath': flipchartPath,
      'uncompressPath': uncompressPath
    });
    return result;
  }

  static Future<String> loadPage(int pageNumber) async {
    final String result = await _channel.invokeMethod('loadPage',
        <String, dynamic>{'pageNumber': pageNumber});
    return result;
  }

  static Future clear() async{
    await _channel.invokeMethod('clear');
  }

  static Future dispose() async{
    await _channel.invokeMethod('dispose');
  }

}
