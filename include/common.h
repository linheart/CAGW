#ifndef COMMON_H // COMMON_H
#define COMMON_H

#include <algorithm>
#include <cmath>
#include <codecvt>
#include <cwctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const wstring password = L"CAGW";

void remove_spaces(wstring &text);
wstring up_to_lower(const wstring);
string wstring_to_string(const wstring &);
void print_error(const string &);
bool login();
void menu();
void clear_buffer();

#endif // COMMON_H
