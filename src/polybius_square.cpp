#include "../include/polybius_square.h"

wstring polybius_square_decryption(const wstring text, const square sq) {
  wstring decrypted_text = L"";
  size_t index = 0;
  size_t size = sq.size();
  for (wchar_t wch : text) {
    if (iswalpha(wch)) {
      index = symb_num(wch, sq);
      if (index != static_cast<size_t>(-1)) {
        if (sq[(index / 10 - 1) % size][index % 10] == L'-') {
          index -= 10;
        }
        decrypted_text += sq[(index / 10 - 1) % size][index % 10];
      } else {
        decrypted_text += wch;
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

wstring polybius_square_encryption(const wstring text, const square sq) {
  wstring enctypted_text = L"";
  size_t size = sq.size();
  size_t index = 0;
  for (wchar_t wch : text) {
    if (iswalpha(wch)) {
      index = symb_num(wch, sq);
      if (index != static_cast<size_t>(-1)) {
        if (sq[(index / 10 + 1) % size][index % 10] == L'-') {
          index += 10;
        }
        enctypted_text += sq[(index / 10 + 1) % size][index % 10];
      } else {
        enctypted_text += wch;
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
