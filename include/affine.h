#ifndef AFFINE_H // AFFINE_H
#define AFFINE_H

#include "common.h"

int ex_euclid(int, int);
wchar_t determine_letter(wchar_t);
wstring affine_decrypt(int, int, int, wstring);
wstring affine_encrypt(int, int, int, wstring);

void affine_menu();

#endif // AFFINE_H
