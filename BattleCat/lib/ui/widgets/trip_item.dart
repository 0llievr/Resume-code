/*
import 'package:grampacker/models/battle.dart';
import 'package:flutter/material.dart';

class TripItem extends StatelessWidget {
  final Trip trip;
  final Function onDeleteItem;
  const TripItem({Key key, this.trip, this.onDeleteItem}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Card(
      margin: const EdgeInsets.only(top: 20),
      child: InkWell(
        child: Row(
          children: <Widget>[
            Expanded(
                child: Padding(
              padding: const EdgeInsets.only(left: 15.0),
              child: Text(trip.title),
            )),
            IconButton(
              icon: Icon(Icons.close),
              onPressed: () {
                if (onDeleteItem != null) {
                  onDeleteItem();
                }
              },
            ),
          ],
        ),
      ),
    );
  }
}
*/