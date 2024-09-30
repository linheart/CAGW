#include "../include/polybius_square.h"

wstring polybius_square_decryption(const wstring text) {
  square ru_sq = ru_square();
  square en_sq = en_square();
  square sq;
  wstring decrypted_text = L"";
  size_t index = 0;
  size_t size;

  for (wchar_t wch : text) {
    if (iswalpha(wch)) {
      sq = isalpha(wch) ? en_sq : ru_sq;
      size = sq.size();
      index = symb_num(wch, sq);
      if (index < 10) {
        index += size * 10;
      }
      if (index != static_cast<size_t>(-1)) {
        if (sq[(index / 10 - 1) % size][index % 10] == L'-') {
          index -= 10;
        }
        decrypted_text += sq[(index / 10 - 1) % size][index % 10];
      }
    } else {
      decrypted_text += wch;
    }
  }
  return decrypted_text;
}

size_t symb_num(const wchar_t target, const square sq) {
  size_t size = sq.size();
  size_t index = -1;
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size && index == -1; j++) {
      if (sq[i][j] == target) {
        index = i * 10 + j;
      }
    }
  }
  return index;
}

wstring polybius_square_encryption(const wstring text) {
  square ru_sq = ru_square();
  square en_sq = en_square();
  square sq;
  wstring enctypted_text = L"";
  size_t size;
  size_t index = 0;
  for (wchar_t wch : text) {
    if (iswalpha(wch)) {
      sq = isalpha(wch) ? en_sq : ru_sq;
      size = sq.size();
      index = symb_num(wch, sq);
      if (index != static_cast<size_t>(-1)) {
        if (sq[(index / 10 + 1) % size][index % 10] == L'-') {
          index += 10;
        }
        enctypted_text += sq[(index / 10 + 1) % size][index % 10];
      }
    } else {
      enctypted_text += wch;
    }
  }
  return enctypted_text;
}

square en_square() {
  square sq(5, vector<wchar_t>(5));
  wchar_t letter = L'a';

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++, letter++) {
      if (letter == L'j') {
        letter++;
      }
      sq[i][j] = letter;
    }
  }

  return sq;
}

square ru_square() {
  square sq(6, vector<wchar_t>(6));
  wchar_t letter = L'а';

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++, letter++) {
      if (letter <= L'я') {
        sq[i][j] = letter;
      } else {
        sq[i][j] = L'-';
      }
    }
  }

  return sq;
}

void polybius_menu() {
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

      text = up_to_lower(text);

      if (choice == 1) {
        result = polybius_square_encryption(text);
      } else {
        result = polybius_square_decryption(text);
      }

      if (choose_method(L"Do yow want to write the result to a file? (y/n) ")) {
        wcout << L"Enter the path to the file: ";
        getline(wcin, path);

        wofstream file(wstring_to_string(path));

        file << result;
      } else {
        wcout << result << endl;
      }

      return;

    } catch (const runtime_error &e) {
      wcout << L"Runtime error: ";
      print_error(e.what());
    } catch (const exception &e) {
      wcout << typeid(e).name() << endl;
    }
  }
}
