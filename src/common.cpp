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