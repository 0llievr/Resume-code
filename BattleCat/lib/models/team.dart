class Team {
  String name;
  String documentId;

  Team({this.name, this.documentId});

  static Team fromMap(Map<String, dynamic> map, String documentId) {
    if (map == null) return null;

    return Team(
      documentId: documentId,
      name: map['name'],
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
    };
  }
}
