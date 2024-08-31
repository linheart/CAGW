#include "../include/affine.h"
#include "../include/common.h"
#include "../include/polybius_square.h"
#include "../include/tabular_encrypt.h"

int main() {
  locale::global(locale("ru_RU.UTF-8"));
  try {
    bool log = login();
    if (log) {
      menu();
    }
  } catch (const exception &e) {
    wcout << typeid(e).name() << endl;
  }
  return 0;

  /*wstring key = L"хуй";*/
  /*wstring text = L"ппошла нахуй гнида ебаная";*/
  /**/
  /*wstring a = tab_encrypt(text, key);*/
  /*wcout << a << endl;*/
  /*wcout << tab_decrypt(a, key);*/
  /*wstring text = input;*/

  // wcout << L"Input key: ";
  // wstring key_word;
  // wcin >> key_word;

  // wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

  // wcout << L"Input text:" << endl;

  // wstring input;
  // getline(wcin, input);

  // wstring text = up_to_lower(input);

  // wstring encrypted_text = encrypt_text(text, key_word);
  // wcout << encrypted_text << endl;

  // wstring decrypter_text = decrypt_text(encrypted_text, key_word);
  // wcout << decrypter_text << endl;

  /*wstring text = up_to_lower(input);*/
  /**/
  /*square en_sq = en_square();*/
  /*square ru_sq = ru_square();*/
  /**/
  /*wstring encrypted_text = polybius_square_encryption(input, ru_sq);*/
  /*wcout << encrypted_text << endl;*/
  /*wcout << polybius_square_decryption(encrypted_text, ru_sq);*/

  return 0;
}
bool login() {
  wstring input_password;

  try {
    wcout << L"Input password: ";
    getline(wcin, input_password);

    if (input_password == password) {
      return true;
    } else {
      throw runtime_error(wstring_to_string(L"Wrong password!"));
    }
  } catch (const runtime_error &e) {
    wcout << L"Runtime error: ";
    print_error(e.what());
    return false;
  } catch (const exception &e) {
    wcout << typeid(e).name() << endl;
    return false;
  }

  return false;
}

void menu() {
  int choice;
  wcout << L"\033[2J\033[0;0f";

  while (true) {
    try {
      wcout << L"1 - Affine" << endl;
      wcout << L"2 - Polybius square" << endl;
      wcout << L"3 - Tabular" << endl;
      wcout << L"4 - Quit" << endl;

      if (!(wcin >> choice)) {
        throw runtime_error(
            wstring_to_string(L"Incorrect input! Enter a number."));
      }

      switch (choice) {
      case 1:
        affine_menu();
        break;
      case 2:
        wcout << L"2" << endl;
        break;
      case 3:
        wcout << L"3" << endl;
        break;
      case 4:
        return;
      default:
        throw runtime_error("There's no option!");
      }
    } catch (const runtime_error &e) {
      wcout << L"Runtime error ";
      print_error(e.what());
      clear_buffer();
    } catch (const exception &e) {
      wcout << typeid(e).name() << endl;
      clear_buffer();
    }
  }
}
