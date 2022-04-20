import 'package:flutter/foundation.dart';

import 'cat.dart';

class Battle {
  @required
  Cat cat1;
  @required
  Cat cat2;
  final String battleDocumentId;
  Battle({this.cat1, this.cat2, this.battleDocumentId});

  Map<String, dynamic> toMap() {
    return {
      'cat1': cat1,
      'cat2': cat2,
      'battleDocumentId': battleDocumentId,
    };
  }

  static Battle fromMap(Map<String, dynamic> map, String documentId) {
    if (map == null) return null;
    return Battle(
      cat1: map['cat1'],
      cat2: map['cat2'],
      battleDocumentId: documentId,
    );
  }
}
