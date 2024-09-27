#ifndef AFFINE_H // AFFINE_H
#define AFFINE_H

#include "common.h"
#include <random>

int ex_euclid(int, int);
int gcd(int, int);
int gen_rand_num(int);
int gen_coprime_num(int);
wchar_t determine_letter(wchar_t);
wstring affine_decrypt(int, int, int, int, int, int, wstring);
wstring affine_encrypt(int, int, int, int, int, int, wstring);

void affine_menu();

#endif // AFFINE_H
