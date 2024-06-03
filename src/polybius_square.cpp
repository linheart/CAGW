#include "../include/polybius_square.h"
#include "../include/common.h"

wstring polybius_square_decryption(const wstring text, const square sq) {
  wstring decrypted_text = L"";
  for (size_t i = 0; i < text.size(); i += 2) {
    int num = stoi(text.substr(i, 2));
    decrypted_text += sq[num / 10 - 1][num % 10 - 1];
  }
  return decrypted_text;
}

int find_symb_numb(const wchar_t target, const square sq) {
  for (size_t i = 0; i < sq.size(); i++) {
    for (size_t j = 0; j < sq[i].size(); j++) {
      if (sq[i][j] == target && target != L'-') {
        return (i + 1) * 10 + j + 1;
      }
    }
  }

  return 0;
}

wstring polybius_square_encryption(const wstring text, const square sq) {
  wstring enctypted_text = L"";
  int num = 0;
  for (auto wch : text) {
    num = find_symb_numb(wch, sq);
    if (num) {
      enctypted_text += to_wstring(num);
    } else {
      enctypted_text += L" ";
    }
  }
  return enctypted_text;
}

square en_square() {
  square sq(5, vector<wchar_t>(5));
  wchar_t letter = L'a';

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      sq[i][j] = letter++;
      if (letter == L'j') letter++;
    }
  }

  return sq;
}

square ru_square() {
  square sq(6, vector<wchar_t>(6));
  wchar_t letter = L'а';

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++, letter++) {
      sq[i][j] = letter;
      if (letter > L'я') sq[i][j] = L'-';
    }
  }

  return sq;
}

wstring up_to_lower(const wstring input) {
  wstring lower_cased = L"";
  for (wchar_t c : input) {
    lower_cased += tolower(c, locale());
  }
  return lower_cased;
}