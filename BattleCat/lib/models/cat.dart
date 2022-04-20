import 'package:flutter/foundation.dart';

class Cat {
  final String name;
  final String trainerId;
  final double attack;
  final double hp;
  final String imageUrl;
  final String documentId;

  Cat({
    @required this.name,
    @required this.trainerId,
    this.attack,
    this.hp,
    this.imageUrl,
    this.documentId,
  });

  static Cat fromMap(Map<String, dynamic> map, String documentId) {
    if (map == null) return null;
    assert(map["name"] != null);
    return Cat(
      name: map['name'],
      attack: map['attack'],
      hp: map['hp'],
      imageUrl: map['imageUrl'],
      trainerId: map['trainerId'],
      documentId: documentId,
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'attack': attack,
      'hp': hp,
      'imageUrl': imageUrl,
      'documentId': documentId,
    };
  }
}
