import 'dart:async';
import 'dart:io';

import 'package:file_picker/file_picker.dart';
import 'package:flipchartparser/flipchartparser.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:lite_log/lite_log.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';

  @override
  void initState() {
    super.initState();
    initPlatformState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    String platformVersion;
    // Platform messages may fail, so we use a try/catch PlatformException.
    try {
      //platformVersion = await Flipchartparser.platformVersion;
    } on PlatformException {
      platformVersion = 'Failed to get platform version.';
    }

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _platformVersion = platformVersion;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: IconButton(
              icon: Icon(Icons.open_in_browser),
              onPressed: () async {
                FlipchartParserGlobalconfig(
                    tempPath: Directory.systemTemp.path);
                File file = await FilePicker.getFile();
                FlipchartParser parser = new FlipchartParser();
                LogUtil.i(content: await parser.openFlipchart(file.path));
                String content = await parser.loadPage(0);
                print(content);
              }),
        ),
      ),
    );
  }
}
