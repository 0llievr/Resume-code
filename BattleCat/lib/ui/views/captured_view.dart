import 'package:firebase_auth/firebase_auth.dart';
import 'package:grampacker/locator.dart';
import 'package:grampacker/services/firestore_service.dart';
import 'package:grampacker/ui/widgets/helpers/input_field.dart';
import 'package:grampacker/viewmodels/captured_view_model.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:stacked/stacked.dart';

class CaptureView extends StatelessWidget {
  final _nameController = TextEditingController();

  final imageFile;
  final FirestoreService _firestoreService = locator<FirestoreService>();

  CaptureView({Key key, @required this.imageFile}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var currentUserId = Provider.of<User>(context).uid;
    return ViewModelBuilder<CapturedViewModel>.reactive(
      viewModelBuilder: () => CapturedViewModel(),
      builder: (context, model, child) => Scaffold(
        body: Stack(
          children: [
            InkWell(
              onTap: model.addImage,
              child: Image.file(imageFile),
            ),
            CustomScrollView(
              slivers: [
                SliverAppBar(
                  elevation: 0,
                  expandedHeight: 250,
                  backgroundColor: Colors.transparent,
                  leading: Align(
                    child: InkWell(
                      onTap: () {
                        model.back();
                      },
                      child: Container(
                        padding: const EdgeInsets.all(10),
                        decoration: BoxDecoration(
                          shape: BoxShape.circle,
                          color: Colors.white,
                        ),
                        child: Icon(
                          Icons.close_rounded,
                          color: Theme.of(context).accentColor,
                        ),
                      ),
                    ),
                  ),
                  actions: [
                    InkWell(
                      onTap: () async {
                        var imageUrl =
                            await _firestoreService.addImage(imageFile);
                        model.addCat(
                          imageUrl: imageUrl,
                          name: _nameController.text,
                          userId: currentUserId,
                          attack: "6",
                          hp: "7",
                        );
                      },
                      child: Container(
                        padding: const EdgeInsets.all(10),
                        decoration: BoxDecoration(
                          shape: BoxShape.circle,
                          color: Colors.white,
                        ),
                        child: Icon(Icons.done,
                            color: Theme.of(context).accentColor),
                      ),
                    ),
                    const SizedBox(width: 10),
                  ],
                ),
                SliverToBoxAdapter(
                  child: Container(
                    padding: const EdgeInsets.symmetric(horizontal: 20),
                    decoration: BoxDecoration(
                      color: Colors.white,
                      borderRadius: BorderRadius.vertical(
                        top: Radius.circular(20),
                      ),
                    ),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        const SizedBox(height: 20),
                        Center(
                          child: Container(
                            width: 100,
                            height: 5,
                            decoration: BoxDecoration(
                              color: Colors.grey[300],
                              borderRadius: BorderRadius.circular(20),
                            ),
                          ),
                        ),
                        const SizedBox(height: 25),
                        Row(
                          children: [
                            Expanded(
                              child: InputField(
                                placeholder: 'Name',
                                controller: _nameController,
                              ),
                            ),
                            //title
                            const SizedBox(width: 10),
                          ],
                        ),
                        SizedBox(
                          height: 100,
                        ),
                      ],
                    ),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
