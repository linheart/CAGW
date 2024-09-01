#ifndef POLYBUIS_SQUARE_H // POLYBUIS_SQUARE_H
#define POLYBUIS_SQUARE_H

#include "common.h"
#include <string>
#include <vector>

using square = vector<vector<wchar_t>>;

wstring polybius_square_decryption(const wstring);
size_t symb_num(const wchar_t, const square);
wstring polybius_square_encryption(const wstring);
square en_square();
square ru_square();
void polybius_menu();

#endif // POLYBUIS_SQUARE_H
