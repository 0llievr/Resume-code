import 'dart:async';
import 'dart:io';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_storage/firebase_storage.dart';
import 'package:grampacker/models/cat.dart';
import 'package:grampacker/models/battle.dart';
import 'package:grampacker/models/trainer.dart';
import 'package:flutter/services.dart';

class FirestoreService {
  final Reference firestoreReference = FirebaseStorage.instance.ref();

  final CollectionReference _usersCollectionReference =
      FirebaseFirestore.instance.collection('users');

  final CollectionReference _battlesCollectionReference =
      FirebaseFirestore.instance.collection('battles');

  final CollectionReference _catsCollectionReference =
      FirebaseFirestore.instance.collection('cats');

  final StreamController<Battle> _battleController =
      StreamController<Battle>.broadcast();

  final StreamController<List<Battle>> _battlesController =
      StreamController<List<Battle>>.broadcast();

  final StreamController<List<Cat>> _catsController =
      StreamController<List<Cat>>.broadcast();

  Future createUser(Trainer user) async {
    try {
      print("create user id: " + user.id + '\n');
      await _usersCollectionReference.doc(user.id).set(user.toMap());
    } catch (e) {
      if (e is PlatformException) {
        return e.message;
      }

      return e.toString();
    }
  }

  Future getUser(String uid) async {
    try {
      var userData = await _usersCollectionReference.doc(uid).get();
      return Trainer.fromData(userData.data());
    } catch (e) {
      if (e is PlatformException) {
        return e.message;
      }

      return e.toString();
    }
  }

  Future createBattle(Battle battle) async {
    try {
      await _battlesCollectionReference.add(battle.toMap());
    } catch (e) {
      if (e is PlatformException) {
        return e.message;
      }

      return e.toString();
    }
  }

// prob not needed
  Stream listenToBattlesRealTime() {
    _battlesCollectionReference.snapshots().listen(
      (battlesSnapshot) {
        if (battlesSnapshot.docs.isNotEmpty) {
          var battles = battlesSnapshot.docs
              .map((snapshot) {
                print("ID: " + snapshot.id + '\n');
                return Battle.fromMap(snapshot.data(), snapshot.id);
              })
              .where((mappedItem) =>
                  mappedItem.cat1 != null && mappedItem.cat2 != null)
              .toList();

          _battlesController.add(battles);
        }
      },
    );

    return _battlesController.stream;
  }

  Future getCats() async {
    var qs = await _battlesCollectionReference.get();
    List<Cat> cats;
    if (qs.docs.isNotEmpty) {
      qs.docs.forEach((doc) => cats.add(Cat.fromMap(doc.data(), doc.id)));
    }
    return cats;
  }

  Stream listenToCatRealTime(String uid) {
    final CollectionReference _catsCollectionReference =
        _usersCollectionReference.doc(uid).collection("cats");
    _catsCollectionReference.snapshots().listen(
      (catsSnapshot) {
        if (catsSnapshot.docs.isNotEmpty) {
          var cats = catsSnapshot.docs.map((snapshot) {
            return Cat.fromMap(snapshot.data(), snapshot.id);
          }).toList();

          _catsController.add(cats);
        }
      },
    );

    return _battlesController.stream;
  }

  Future deleteBattle(String documentId) async {
    await _battlesCollectionReference.doc(documentId).delete();
  }

  Stream listenToBattleRealTime(String docId) {
    _battlesCollectionReference.doc(docId).snapshots().listen(
      (tripSnapshot) {
        var trip = Battle.fromMap(tripSnapshot.data(), tripSnapshot.id);
        _battleController.add(trip);
      },
    );
    return _battleController.stream;
  }

  Future<void> addCat(Cat cat) async {
    try {
      await _catsCollectionReference.add(cat.toMap());
    } catch (e) {
      if (e is PlatformException) {
        return e.message;
      }

      return e.toString();
    }
  }

  Stream listenToCatsRealTime(String uid) {
    _catsCollectionReference.snapshots().listen((catSnapshot) {
      if (catSnapshot.docs.isNotEmpty) {
        List<Cat> cats = catSnapshot.docs.map((snapshot) {
          return Cat.fromMap(snapshot.data(), snapshot.id);
        }).toList();

        _catsController.add(cats);
      }
    });

    return _catsController.stream;
  }

  Future<String> addImage(File imageFile) async {
    assert(imageFile != null);
    var upload = await firestoreReference
        .child("assets/images")
        .putFile((imageFile))
        .whenComplete(() => print("uploaded image"));
    return await upload.ref.getDownloadURL();
  }
}
