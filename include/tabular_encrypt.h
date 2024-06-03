#ifndef TABULAR_ENCRYPT_H // TABULAR_ENCRYPT_H
#define TABULAR_ENCRYPT_H

#include "common.h"
#include <utility> 
#include <cmath>

using Table = vector<pair<int, vector<wchar_t>>>;

vector<int> make_alphabet_num(wstring);
int counting_characters(const wstring);
void reverse_sort_table(Table &, const wstring);
void sort_table(Table &);
Table init_table(const wstring, const wstring);
Table make_table(const wstring, const wstring);
wstring decrypt_text(const wstring, const wstring);
wstring encrypt_text(const wstring, const wstring);

#endif // TABULAR_ENCRYPT_H