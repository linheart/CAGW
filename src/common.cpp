#include "../include/common.h"

void remove_spaces(wstring &text) {
  text.erase(remove_if(text.begin(), text.end(),
                       [](wchar_t c) { return iswspace(c); }),
             text.end());
}

wstring up_to_lower(const wstring input) {
  wstring lower_cased = L"";
  for (wchar_t c : input) {
    lower_cased += tolower(c, locale());
  }
  return lower_cased;
}

string wstring_to_string(const wstring &wmsg) {
  wstring_convert<codecvt_utf8<wchar_t>> converter;
  string msg = converter.to_bytes(wmsg);
  return msg;
}

void print_error(const string &e) {
  wstring_convert<codecvt_utf8<wchar_t>> converter;
  wstring wmsg = converter.from_bytes(e);
  wcout << wmsg << endl;
}

void clear_buffer() {
  wcin.clear();
  wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
}

bool choose_method(const wstring &text) {
  wstring method;
  bool choice;

  wcout << text;

  getline(wcin, method);
  method = up_to_lower(method);
  if (method == L"y" || method == L"yes") {
    return true;
  }
  return false;
}

int input_num() {
  int num;
  if (!(wcin >> num)) {
    clear_buffer();
    throw runtime_error(wstring_to_string(L"Enter a number."));
  }
  return num;
}

int choose_interaction() {
  wcout << L"1 - Encrypt" << endl;
  wcout << L"2 - Decrypt" << endl;
  wcout << L"3 - Back" << endl;

  return input_num();
}
