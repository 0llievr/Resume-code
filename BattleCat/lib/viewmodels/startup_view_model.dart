import 'package:grampacker/constants/route_names.dart';
import 'package:grampacker/locator.dart';
import 'package:grampacker/services/authentication_service.dart';
import 'package:grampacker/services/navigation_service.dart';
import 'package:grampacker/viewmodels/base_model.dart';

class StartUpViewModel extends BaseModel {
  final AuthenticationService _authenticationService =
      locator<AuthenticationService>();
  final NavigationService _navigationService = locator<NavigationService>();

  Future handleStartUpLogic() async {
    var hasLoggedInUser = await _authenticationService.isUserLoggedIn();

    if (hasLoggedInUser) {
      _navigationService.pop();
      _navigationService.navigateTo(HomeViewRoute);
    } else {
      _navigationService.pop();
      _navigationService.navigateTo(LoginViewRoute);
    }
  }
}
