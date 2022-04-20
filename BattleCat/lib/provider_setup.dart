import 'package:firebase_auth/firebase_auth.dart';
import 'package:grampacker/locator.dart';
import 'package:provider/provider.dart';
import 'package:provider/single_child_widget.dart';

import 'services/authentication_service.dart';

List<SingleChildWidget> providers = [
  ...independentServices,
  ...dependentServices,
  ...uiConsumableProviders
];

List<SingleChildWidget> independentServices = [
  StreamProvider<User>(
    initialData: null,
    create: (context) => locator<AuthenticationService>().authStream,
  ),
];

List<SingleChildWidget> dependentServices = [];

List<SingleChildWidget> uiConsumableProviders = [];
