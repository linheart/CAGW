#include "../include/common.h"
#include "../include/polybius_square.h"
#include "../include/tabular_encrypt.h"
/*
 сделать проверку на вводимые числа.
 в функции ind_symb_numb оставить только один выход из функции.
*/

int main() {
  locale::global(locale("ru_RU.UTF-8"));

  wcout << L"Input key: ";
  wstring key_word;
  wcin >> key_word;

  wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

  wcout << L"Input text:" << endl;

  wstring input;
  getline(wcin, input);

  Table table = make_table(input, key_word);

  sort(table.begin(), table.end(),
       [](const pair<int, vector<wchar_t>> a,
          const pair<int, vector<wchar_t>> b) { return a.first < b.first; });

  for (size_t i = 0; i < key_word.size(); i++) {
    if (table[i].second.size() > 0) {
      for (size_t j = 0; j < table[i].second.size(); j++) {
        wcout << table[i].second[j];
      }
      wcout << ' ';
    }
  }

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
