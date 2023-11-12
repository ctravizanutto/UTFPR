import 'package:firebase_auth/firebase_auth.dart';
import 'package:get/get.dart';
import 'package:sqlite3/sqlite3.dart';
import 'package:vwalltet/controllers/card_controller.dart';
import 'package:vwalltet/services/db_service.dart';

class AuthService {
  static final FirebaseAuth _auth = FirebaseAuth.instance;

  static User? get user => _auth.currentUser;
  static AuthService get to => Get.find();

  showSnack(String titulo, String erro) {
    Get.snackbar(
      titulo,
      erro,
      snackPosition: SnackPosition.BOTTOM,
    );
  }

  newUser(String email, String password) async {
    try {
      await _auth.createUserWithEmailAndPassword(
          email: email, password: password);
      DatabaseService().db.prepare('INSERT INTO ')
    } catch (e) {
      showSnack('Erro ao criar usuário.', '$e');
      rethrow;
    }
  }

  login(String email, String password) async {
    try {
      await _auth.signInWithEmailAndPassword(
        email: email,
        password: password,
      );
    } on FirebaseAuthException catch (e) {
      showSnack('Erro ao logar.', e.message!);
      rethrow;
    }
  }

  signOut() async {
    try {
      _auth.signOut();
    } catch (e) {
      showSnack('ERRO', '$e');
    }
  }
}
