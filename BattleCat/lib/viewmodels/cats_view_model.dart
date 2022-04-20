import 'package:grampacker/locator.dart';
import 'package:grampacker/models/cat.dart';
import 'package:grampacker/services/dialog_service.dart';
import 'package:grampacker/services/firestore_service.dart';
import 'package:grampacker/services/navigation_service.dart';
import 'package:grampacker/viewmodels/base_model.dart';

class CatsHomeViewModel extends BaseModel {
  final NavigationService _navigationService = locator<NavigationService>();
  final FirestoreService _firestoreService = locator<FirestoreService>();
  final DialogService _dialogService = locator<DialogService>();

  CatsHomeViewModel(this._cats);

  final List<Cat> _cats;
  List<Cat> get cats => _cats;

/*
  Future deleteInventoryItem(int index, String userId) async {
    var dialogResponse = await _dialogService.showConfirmationDialog(
      title: 'Are you sure?',
      description: 'Do you really want to delete this gear item?',
      confirmationTitle: 'Yes',
      cancelTitle: 'No',
    );

    if (dialogResponse.confirmed) {
      setBusy(true);
      await _firestoreService.deleteCat(
          itemId: _inventory[index].documentId, userId: userId);
      setBusy(false);
    }
  }

  // inventory navigation
  Future navigateToInventoryCreateView() async {
    await _navigationService.navigateTo(CreateInventoryViewRoute);
  }

  Future navigateToInventoryDetailsView(GearItem item) async {
    await _navigationService.navigateTo(InventoryDetailsViewRoute,
        arguments: item);
  }
  */
}
