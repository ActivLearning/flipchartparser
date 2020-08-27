import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flipchartparser/flipchartparser.dart';

void main() {
  const MethodChannel channel = MethodChannel('flipchartparser');

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await Flipchartparser.platformVersion, '42');
  });
}
