#ifndef POLYBUIS_SQUARE_H // POLYBUIS_SQUARE_H
#define POLYBUIS_SQUARE_H

#include "common.h"

using square = vector<vector<wchar_t>>;


wstring polybius_square_decryption(const wstring, const square);
int find_symb_numb(const wchar_t, const square);
wstring polybius_square_encryption(const wstring, const square);
square en_square();
square ru_square();

#endif //POLYBUIS_SQUARE_H