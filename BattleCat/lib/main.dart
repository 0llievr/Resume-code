import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:grampacker/services/dialog_service.dart';
import 'package:grampacker/services/navigation_service.dart';
import 'package:grampacker/ui/views/startup_view.dart';
import 'package:provider/provider.dart';
import 'managers/dialog_manager.dart';
import 'provider_setup.dart';
import 'ui/router.dart';
import 'locator.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  setupLocator();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final Future<FirebaseApp> _init = Firebase.initializeApp();

  @override
  Widget build(BuildContext context) {
    return FutureBuilder(
      future: _init,
      builder: (context, snapshot) {
        if (snapshot.hasError) {
          //errorscreen
        }
        if (snapshot.connectionState == ConnectionState.done) {
          return MultiProvider(
            providers: providers,
            builder: (context, child) => MaterialApp(
              builder: (context, child) => Navigator(
                key: locator<DialogService>().dialogNavigationKey,
                onGenerateRoute: (settings) => MaterialPageRoute(
                    builder: (context) => DialogManager(child: child)),
              ),
              navigatorKey: locator<NavigationService>().navigationKey,
              theme: ThemeData(
                primaryColor: Colors.deepOrange,
              ),
              home: StartUpView(),
              onGenerateRoute: generateRoute,
            ),
          );
        }
        return CircularProgressIndicator();
      },
    );
  }
}
