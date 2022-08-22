import 'package:led/modeselect.dart';
import 'package:led/websocket.dart';
import 'package:flutter/material.dart';
// ignore: import_of_legacy_library_into_null_safe
import 'package:splashscreen/splashscreen.dart';

class Splash2 extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return SplashScreen(
      backgroundColor: Colors.black,
      seconds: 2,
      navigateAfterSeconds: modeselect(),
      // title: new Text('Reverse Vending Machine',
      //     textScaleFactor: 1.5, style: TextStyle(color: Colors.yellow)),
      image: Image.asset(
        'assets/images/esp8266logo.png',
        fit: BoxFit.fill,
      ),
      loadingText: Text("Controlling on your finger tips",
          style: TextStyle(
              color: Color.fromARGB(255, 199, 255, 233), fontSize: 18.0)),
      photoSize: 125.0,
      loaderColor: Color.fromARGB(255, 199, 255, 233),
    );
  }
}
