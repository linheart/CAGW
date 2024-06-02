#include "../include/polybius_square.h"

/*
 сделать проверку на вводимые числа.
 в функции ind_symb_numb оставить только один выход из функции.
*/

int main() {
  locale::global(locale("ru_RU.UTF-8"));
  wstring input;
  getline(wcin, input);

  wstring text = up_to_lower(input);

  square en_sq = en_square();
  square ru_sq = ru_square();

  wcout << polybius_square_encryption(L"lol", en_sq) << endl;
  wcout << polybius_square_encryption(L"мпм", ru_sq) << endl;

  wcout << polybius_square_decryption(L"313431", en_sq) << endl;
  wcout << polybius_square_decryption(L"313431", ru_sq) << endl;
  return 0;
}
