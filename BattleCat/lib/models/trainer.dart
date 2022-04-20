class Trainer {
  final String id;
  final String fullName;
  final String email;
  final String userRole;

  Trainer({this.id, this.fullName, this.email, this.userRole});

  Trainer.fromData(Map<String, dynamic> data)
      : id = data['id'],
        fullName = data['fullName'],
        email = data['email'],
        userRole = data['userRole'];

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'fullName': fullName,
      'email': email,
      'userRole': userRole,
    };
  }
}
