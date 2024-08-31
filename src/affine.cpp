#include "../include/affine.h"

int ex_euclid(int c, int m) {
  int x = 0, y = 1, lastx = 1, lasty = 0, temp;
  while (m != 0) {
    int q = c / m;
    int r = c % m;

    c = m;
    m = r;

    temp = x;
    x = lastx - q * x;
    lastx = temp;

    temp = y;
    y = lasty - q * y;
    lasty = temp;
  }
  return lastx;
}

wchar_t determine_letter(wchar_t wch) {
  if (wch >= L'A' && wch <= L'z') {
    wch = iswlower(wch) ? L'a' : L'A';
  } else {
    wch = iswlower(wch) ? L'а' : L'А';
  }
  return wch;
}

wstring affine_decrypt(int a, int b, int m, wstring text) {
  wstring decrypted_text = L"";
  wchar_t base;
  int coprime = (ex_euclid(a, m) % m + m) % m;
  for (wchar_t symb : text) {
    if (iswalpha(symb)) {
      base = determine_letter(symb);
      decrypted_text += coprime * ((symb - base) + m - b) % m + base;
    } else {
      decrypted_text += symb;
    }
  }
  return decrypted_text;
}

wstring affine_encrypt(int a, int b, int m, wstring text) {
  wstring encrypted_text = L"";
  wchar_t base;
  for (wchar_t symb : text) {
    if (iswalpha(symb)) {
      base = determine_letter(symb);
      encrypted_text += (a * (symb - base) + b) % m + base;
    } else {
      encrypted_text += symb;
    }
  }
  return encrypted_text;
}

bool choose_method() {
  wstring method;
  bool choice;

  wcout << L"Do you want to read data from a file: (y/n) ";

  getline(wcin, method);
  method = up_to_lower(method);
  if (method == L"y" || method == L"yes") {
    return true;
  }
  return false;
}

void affine_menu() {
  unsigned a;
  unsigned b;
  unsigned m = 32;
  wstring path;
  wstring text;

  wcout << L"\033[2J\033[0;0f";
  wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

  while (true) {
    try {
      if (choose_method()) {
        wcout << L"Enter the path to the file: ";
        getline(wcin, path);

        wifstream file(wstring_to_string(path));

        if (!file.is_open()) {
          wcout << "Incorrect path" << endl;
        }

        if (!(file >> a >> b)) {
          throw runtime_error("FUCK");
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(file, text);

        file.close();

      } else {
        wcout << L"Enter a b: ";
        if (!(wcin >> a >> b)) {
          throw runtime_error(wstring_to_string(L"Enter a number."));
        }

        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        wcout << L"Enter the text: ";
        getline(wcin, text);
      }
      if (a >= m) {
        throw out_of_range(wstring_to_string(L"A must be less than m"));
      }
      if (ex_euclid(a, m) == 1 && a != 1) {
        throw runtime_error(wstring_to_string(L"The numbers must be coprime"));
      }

      b %= m;
      wstring encrypted_text = affine_encrypt(a, b, m, text);
      wcout << encrypted_text << endl;

      wstring decrypted_text = affine_decrypt(a, b, m, encrypted_text);
      wcout << decrypted_text << endl;

      return;

    } catch (const runtime_error &e) {
      wcout << L"Runtime error: ";
      print_error(e.what());
      clear_buffer();
    } catch (const out_of_range &e) {
      wcout << L"Out of range: ";
      print_error(e.what());
      clear_buffer();
    } catch (const exception &e) {
      wcout << typeid(e).name() << endl;
      clear_buffer();
    }
  }
}
