#ifndef AFFINE_H // AFFINE_H
#define AFFINE_H

#include "common.h"

int ex_euclid(int, int);
wstring affine_decrypt(int, int, int, wstring);
wstring affine_encrypt(int, int, int, wstring);

#endif // AFFINE_H