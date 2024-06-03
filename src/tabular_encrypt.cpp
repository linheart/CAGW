#include "../include/tabular_encrypt.h"

#include "../include/common.h"

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

void reverse_sort_table(Table &table, const wstring text) {
  for (size_t i = 0, index = 0; i < table[0].second.size(); i++) {
    for (size_t j = 0; j < table.size() && text[index]; j++) {
      if (text[index] == L' ') {
        index++;
      }
      table[j].second[i] = text[index++];
    }
  }
}

void sort_table(Table &table) {
  sort(table.begin(), table.end(),
       [](const pair<int, vector<wchar_t>> a,
          const pair<int, vector<wchar_t>> b) { return a.first < b.first; });
}

Table init_table(const wstring text, const wstring key_word) {
  int rows = key_word.size();
  int cols = ceil((float)counting_characters(text) / rows);
  Table table(rows, {0, vector<wchar_t>(cols)});
  vector<int> nums = make_alphabet_num(key_word);

  size_t index = 0;
  for (int i = 0; i < rows; i++) {
    table[i].first = nums[i];
  }
  return table;
}

Table make_table(const wstring text, const wstring key_word) {
  Table table = init_table(text, key_word);
  size_t index = 0;
  for (int i = 0; i < key_word.size(); i++) {
    for (int j = 0; j < table[0].second.size() && index < text.size();
         index++) {
      if (iswspace(text[index])) {
        continue;
      }
      table[i].second[j++] = text[index];
    }
  }
  return table;
}

wstring decrypt_text(const wstring text, const wstring key_word) {
  Table table = init_table(text, key_word);
  vector<int> nums = make_alphabet_num(key_word);

  sort_table(table);
  reverse_sort_table(table, text);

  wstring encrypted_text = L"";
  for (auto num : nums) {
    auto it = find_if(
        table.begin(), table.end(),
        [num](const pair<int, vector<wchar_t>> &p) { return p.first == num; });
    for (auto ch : it->second) {
      encrypted_text += ch;
    }
  }

  return encrypted_text;
}

wstring encrypt_text(const wstring text, const wstring key_word) {
  Table table = make_table(text, key_word);

  size_t rows = key_word.size();
  size_t cols = table[0].second.size();
  wstring result_string = L"";
  int count = 0;

  sort_table(table);

  for (size_t i = 0; i < cols; i++) {
    for (size_t j = 0; j < rows; j++) {
      if (table[j].second[i]) {
        if (count == cols) {
          result_string += ' ';
          count = 0;
        }
        result_string += table[j].second[i];
        count++;
      }
    }
  }

  return result_string;
}