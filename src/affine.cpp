#include "../include/affine.h"
#include <cstdio>

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

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int gen_rand_num(int m) {
  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<std::mt19937::result_type> dist6(2, m - 1);

  return dist6(rng);
}

int gen_coprime_num(int m) {
  int key;

  do {
    key = gen_rand_num(m);
  } while (gcd(key, m) != 1);

  return key;
}

wchar_t determine_letter(wchar_t wch) {
  if (wch >= L'A' && wch <= L'z') {
    wch = iswlower(wch) ? L'a' : L'A';
  } else {
    wch = iswlower(wch) ? L'а' : L'А';
  }
  return wch;
}

wstring affine_decrypt(int a_ru, int b_ru, int m_ru, int a_en, int b_en,
                       int m_en, wstring text) {
  int a;
  int b;
  int m;
  wstring decrypted_text = L"";
  wchar_t base;
  int coprime;

  for (wchar_t symb : text) {
    if (iswalpha(symb)) {
      if (isalpha(symb)) {
        a = a_en;
        b = b_en;
        m = m_en;
      } else {
        a = a_ru;
        b = b_ru;
        m = m_ru;
      }
      coprime = (ex_euclid(a, m) % m + m) % m;
      base = determine_letter(symb);
      decrypted_text += coprime * ((symb - base) + m - b) % m + base;
    } else {
      decrypted_text += symb;
    }
  }
  return decrypted_text;
}

wstring affine_encrypt(int a_ru, int b_ru, int m_ru, int a_en, int b_en,
                       int m_en, wstring text) {
  int a;
  int b;
  int m;

  wstring encrypted_text = L"";
  wchar_t base;
  for (wchar_t symb : text) {
    if (iswalpha(symb)) {
      if (isalpha(symb)) {
        a = a_en;
        b = b_en;
        m = m_en;
      } else {
        a = a_ru;
        b = b_ru;
        m = m_ru;
      }
      base = determine_letter(symb);
      encrypted_text += (a * (symb - base) + b) % m + base;
    } else {
      encrypted_text += symb;
    }
  }
  return encrypted_text;
}

void affine_menu() {
  int m_ru = 32;
  int a_ru;
  int b_ru;

  int m_en = 26;
  int a_en;
  int b_en;

  wstring path;
  wstring text;
  wstring result;

  wcout << L"\033[2J\033[0;0f";

  while (true) {
    try {
      int choice = choose_interaction();

      if (choice == 3) {
        return;
      } else if (choice > 3 || choice < 1) {
        throw runtime_error("There's no option!");
      }

      wcout << L"\033[2J\033[0;0f";
      wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

      if (choose_method(L"Do you want to read data from a file: (y/n) ")) {
        wcout << L"Enter the path to the file: ";
        getline(wcin, path);

        wifstream file(wstring_to_string(path));

        if (!file.is_open()) {
          throw runtime_error(wstring_to_string(L"Incorrect path"));
        }

        getline(file, text);

        file.close();

      } else {
        wcout << L"Enter the text: ";
        getline(wcin, text);
      }

      if (choice == 1) {
        a_ru = gen_coprime_num(m_ru);
        b_ru = gen_rand_num(m_ru);

        a_en = gen_coprime_num(m_en);
        b_en = gen_rand_num(m_en);

        result = affine_encrypt(a_ru, b_ru, m_ru, a_en, b_en, m_en, text);

        wofstream file("keys.txt");
        file << a_ru << ' ' << b_ru << ' ' << a_en << ' ' << b_en;
        file.close();

      } else {
        wifstream file("keys.txt");

        if (!file.is_open()) {
          throw runtime_error(
              wstring_to_string(L"You have to encrypt the text first"));
        }

        file >> a_ru >> b_ru >> a_en >> b_en;
        file.close();

        remove("keys.txt");

        result = affine_decrypt(a_ru, b_ru, m_ru, a_en, b_en, m_en, text);
      }

      if (choose_method(L"Do yow want to write the result to a file? (y/n) ")) {
        wcout << L"Enter the path to the file: ";
        getline(wcin, path);

        wofstream file(wstring_to_string(path));

        file << result;
        file.close();
      } else {
        wcout << result << endl;
      }

      return;

    } catch (const runtime_error &e) {
      wcout << L"Runtime error: ";
      print_error(e.what());
    } catch (const out_of_range &e) {
      wcout << L"Out of range: ";
      print_error(e.what());
    } catch (const exception &e) {
      wcout << typeid(e).name() << endl;
    }
  }
}
