#include "../include/common.h"
#include "../include/tabular_encrypt.h"

vector<int> make_alphabet_num(wstring key_word) {
  size_t size = key_word.size();
  vector<int> nums(size);
  wstring sorted_key_word = key_word;

  sort(sorted_key_word.begin(), sorted_key_word.end());

  for (size_t i = 0; i < size; i++) {
    auto index = key_word.find(sorted_key_word[i]);
    nums[index] = i + 1;
    key_word[index] = L'\0';
  }

  return nums;
}

int counting_characters(const wstring text) {
  int count = 0;
  for (auto wch : text) {
    if (!iswspace(wch)) {
      count++;
    }
  }
  return count;
}

Table make_table(const wstring text, const wstring key_word) {
  int rows = ceil((float)counting_characters(text) / key_word.size());
  int cols = key_word.size();
  Table table(cols);
  vector<int> nums = make_alphabet_num(key_word);
  
  size_t index = 0;
  for (int i = 0; i < cols; i++) {
    table[i].first = nums[i];
    for (int j = 0; j < rows && index < text.size(); index++) {
      if (iswspace(text[index])) {
        continue;
      }
      table[i].second.push_back(text[index]);
      j++;
    }
  }
  return table;  
}