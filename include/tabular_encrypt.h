#ifndef TABULAR_ENCRYPT_H // TABULAR_ENCRYPT_H
#define TABULAR_ENCRYPT_H

#include "common.h"
#include <utility> 
#include <cmath>

using Table = vector<pair<int, vector<wchar_t>>>;

vector<int> make_alphabet_num(wstring);
int counting_characters(const wstring);
Table make_table(const wstring, const wstring);

void NewFunction(int cols, Table &table, std::vector<int> &nums, int rows, const std::wstring &text);

#endif // TABULAR_ENCRYPT_H