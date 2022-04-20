import 'package:flutter/material.dart';
import 'package:grampacker/models/cat.dart';
import 'package:grampacker/ui/widgets/cat_item.dart';
import 'package:grampacker/viewmodels/home_view_model.dart';

class CatList extends StatelessWidget {
  final HomeViewModel model;
  const CatList({Key key, this.model}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    List<Cat> trips = model.cats;
    return trips != null
        ? ListView.builder(
            itemCount: trips.length,
            itemBuilder: (context, index) => GestureDetector(
              //onTap: () => model.navigateToCatsDetailsView(index),
              child: CatItem(
                cat: trips[index],
                //onDeleteItem: () => model.deleteTrip(index),
                //onTap: () => model.navigateToTripDetailsView(index)),
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
