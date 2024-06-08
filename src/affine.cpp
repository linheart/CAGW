#include "../include/affine.h"

int ex_euclid(int c, int m) {
  int x = 0, y = 1, lastx = 1, lasty = 0, temp;
  while (m != 0) {
    int q = c / m;
    int r = c % m;

    c = m;
    m = r;

    temp = x;
    x = lastx - q * x;
    lastx = temp;

    temp = y;
    y = lasty - q * y;
    lasty = temp;
  }
  return lastx;
}

wstring affine_decrypt(int a, int b, int m, wstring text) {
  wstring decrypted_text = L"";
  int coprime = (ex_euclid(a, m) % m + m) % m;
  for (auto it : text) {
    decrypted_text += coprime * (it - 97 + m - b) % m + 97;
  }
  return decrypted_text;
}

wstring affine_encrypt(int a, int b, int m, wstring text) {
  wstring encrypted_text = L"";
  for (auto it : text) {
    encrypted_text += (a * (it - 97) + b) % m + 97;
  }
  return encrypted_text;
}