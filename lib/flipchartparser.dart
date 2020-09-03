import 'dart:async';

import 'package:flutter/services.dart';

const MethodChannel _channel = const MethodChannel('flipchartparser');
Future<void> config(String tempPath, bool logEnabled) async {
  await _channel.invokeMethod("config",
      <String, dynamic>{'tempPath': tempPath, 'logEnabled': logEnabled});
}

class FlipchartParser {
  int _handle = -1;
  Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  Future<void> init() async {
    if (_handle == -1) {
      _handle = await _channel.invokeMethod("newInstance");
    }
  }

  Future<String> openFlipchart(String flipchartPath) async {
    await init();
    final String result = await _channel.invokeMethod('openFlipchart',
        <String, dynamic>{'handle': _handle, 'flipchartPath': flipchartPath});
    return result;
  }

  Future<String> loadPage(int pageNumber) async {
    await init();
    final String result = await _channel.invokeMethod('loadPage',
        <String, dynamic>{'handle': _handle, 'pageNumber': pageNumber});
    return result;
  }

  Future<void> disposed() async {
    await init();
    await _channel
        .invokeMethod('disposed', <String, dynamic>{'handle': _handle});
  }
}
