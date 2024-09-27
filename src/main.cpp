#include "../include/affine.h"
#include "../include/common.h"
#include "../include/polybius_square.h"
#include "../include/tabular.h"

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
  wcout << L"\033[2J\033[0;0f";

  while (true) {
    try {
      wcout << L"1 - Affine" << endl;
      wcout << L"2 - Polybius square" << endl;
      wcout << L"3 - Tabular" << endl;
      wcout << L"4 - Quit" << endl;

      int choice = input_num();

      switch (choice) {
      case 1:
        affine_menu();
        break;
      case 2:
        polybius_menu();
        break;
      case 3:
        tab_menu();
        break;
      case 4:
        return;
      default:
        throw runtime_error("There's no option!");
      }
    } catch (const runtime_error &e) {
      wcout << L"Runtime error: ";
      print_error(e.what());
      clear_buffer();
    } catch (const exception &e) {
      wcout << typeid(e).name() << endl;
      clear_buffer();
    }
  }
}
