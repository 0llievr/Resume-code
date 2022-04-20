import 'package:firebase_auth/firebase_auth.dart';
import 'package:grampacker/viewmodels/home_view_model.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:stacked/stacked.dart';

class HomeView extends StatelessWidget {
  const HomeView({Key key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var tabs = ["Battles", "", "Cats"];
    return ViewModelBuilder<HomeViewModel>.reactive(
        viewModelBuilder: () => HomeViewModel(),
        onModelReady: (model) {
          print(Provider.of<User>(context).uid);
          model.listenToCats(Provider.of<User>(context).uid);
        },
        builder: (context, model, child) => Scaffold(
              appBar: AppBar(title: Text(tabs.elementAt(model.navBarState))),
              body: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 10),
                child: Column(
                  mainAxisSize: MainAxisSize.max,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: <Widget>[
                    Expanded(
                      child: model.selectedPage(model),
                    )
                  ],
                ),
              ),
              bottomNavigationBar: BottomNavigationBar(
                type: BottomNavigationBarType.fixed,
                items: [
                  BottomNavigationBarItem(
                    icon: Icon(Icons.bolt),
                    label: 'Battles',
                  ),
                  BottomNavigationBarItem(
                    icon: Icon(Icons.photo_camera),
                    label: 'Capture',
                  ),
                  BottomNavigationBarItem(
                    icon: Icon(Icons.list),
                    label: 'Cats',
                  ),
                ],
                currentIndex: model.navBarState,
                onTap: model.setAppbarState,
              ),
            ));
  }
}
