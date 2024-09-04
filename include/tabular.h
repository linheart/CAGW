#ifndef TABULAR_H // TABULAR_H
#define TABULAR_H

#include "common.h"

using Table = vector<pair<int, vector<wchar_t>>>;

vector<int> make_alphabet_num(wstring);
void remove_spaces(wstring &);
void reverse_sort_table(Table &, const wstring, vector<int>);
void sort_table(Table &);
Table init_table(const wstring, const wstring);
Table make_table(const wstring, const wstring);
wstring tab_decrypt(wstring, const wstring);
wstring tab_encrypt(wstring, const wstring);
void tab_menu();

#endif // TABULAR_H
