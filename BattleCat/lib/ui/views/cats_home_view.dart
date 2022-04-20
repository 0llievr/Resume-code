import 'package:firebase_auth/firebase_auth.dart';
import 'package:grampacker/models/cat.dart';
import 'package:flutter/material.dart';
import 'package:grampacker/ui/widgets/cat_item.dart';
import 'package:grampacker/viewmodels/cats_view_model.dart';
import 'package:provider/provider.dart';
import 'package:stacked/stacked.dart';

class CatsHomeView extends StatelessWidget {
  const CatsHomeView({Key key, this.cats}) : super(key: key);

  final List<Cat> cats;

  @override
  Widget build(BuildContext context) {
    User curUser = Provider.of(context);
    print("cats" + cats.toString());
    return curUser != null
        ? ViewModelBuilder<CatsHomeViewModel>.reactive(
            viewModelBuilder: () => CatsHomeViewModel(cats),
            disposeViewModel: false,
            builder: (context, model, child) => Column(
              mainAxisSize: MainAxisSize.max,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                Expanded(
                  child: cats != null
                      ? ListView.builder(
                          itemCount: cats.length,
                          itemBuilder: (context, index) {
                            print("name: " + cats[index].name.toString());
                            return GestureDetector(
                              //onTap: () =>
                              //    model.navigateToInventoryDetailsView(index),
                              child: Padding(
                                padding: EdgeInsets.symmetric(horizontal: 8),
                                child: CatItem(
                                  cat: cats[index],
                                  // this wont work without an index were getting a GearItem now
                                  //onDeleteItem: () => model.deleteTrip(index),
                                ),
                              ),
                            );
                          })
                      : Center(
                          child: CircularProgressIndicator(
                            valueColor: AlwaysStoppedAnimation(
                                Theme.of(context).primaryColor),
                          ),
                        ),
                )
              ],
            ),
          )
        : CircularProgressIndicator();
  }
}

/*
class CatList extends StatelessWidget {
  final HomeViewModel model;
  const CatList({Key key, this.model}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    List<Cat> cats = model.cats;
    return cats != null
        ? ListView.builder(
            itemCount: cats.length,
            itemBuilder: (context, index) => GestureDetector(
              //onTap: () => model.editTrip(index),
              child: CatItem(
                cat: cats[index],
                onDeleteItem: () => model.deleteCat(index),
              ),
            ),
          )
        : Center(
            child: CircularProgressIndicator(
              valueColor:
                  AlwaysStoppedAnimation(Theme.of(context).primaryColor),
            ),
          );
  }
}
*/