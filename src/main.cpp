#include "../include/affine.h"
#include "../include/common.h"
#include "../include/polybius_square.h"
#include "../include/tabular_encrypt.h"

/*
 сделать проверку на вводимые числа.
 в функции ind_symb_numb оставить только один выход из функции.
 в последнем шифре добавить переменную, которая будет хранить первую букву
 русского или английского алфавита.
*/

int main() {
  locale::global(locale("ru_RU.UTF-8"));
  int a, b;
  int m = 26;
  wcin >> a >> b;

  if (a >= m || b >= m || m % a == 0) {
    wcout << "lol" << endl;
    return 1;
  }

  // wstring l;
  // wcin >> l;

  wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

  wstring input;
  getline(wcin, input);
  wstring text = up_to_lower(input);
  remove_spaces(text);
  wstring encrypetd_text = affine_encrypt(a, b, m, text);
  wcout << encrypetd_text << endl;
  wcout << affine_decrypt(a, b, m, encrypetd_text);

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

  /*
    wstring text = up_to_lower(input);

    square en_sq = en_square();
    square ru_sq = ru_square();

    wcout << polybius_square_encryption(L"lol", en_sq) << endl;
    wcout << polybius_square_encryption(L"мпм", ru_sq) << endl;

    wcout << polybius_square_decryption(L"313431", en_sq) << endl;
    wcout << polybius_square_decryption(L"313431", ru_sq) << endl;
  */
  return 0;
}
