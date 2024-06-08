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

void remove_characters(wstring &text) {
  text.erase(remove_if(text.begin(), text.end(),
                       [](wchar_t c) { return iswspace(c); }),
             text.end());
}

void reverse_sort_table(Table &table, const wstring text, vector<int> nums) {
  size_t rows = table.size();
  size_t cols = table[0].second.size();
  size_t text_size = text.size();
  int missed_let = cols * rows - text_size;
  size_t bad_words = ceil((float)(missed_let) / cols);
  vector<pair<int, int>> bad_word_nums(bad_words);

  for (size_t i = 1; i < bad_words; i++) {
    bad_word_nums[i - 1] = {nums[rows - i], cols};
    missed_let -= cols;
  }

  if (bad_words) {
    bad_word_nums.back() = {nums[rows - bad_words], missed_let};
  }

  for (size_t i = 0, index = 0; i < cols; i++) {
    for (size_t j = 0; j < rows && text[index]; j++) {
      auto it = find_if(
          bad_word_nums.begin(), bad_word_nums.end(),
          [=](const pair<int, int> p) { return p.first == table[j].first; });

      if (it != bad_word_nums.end() && it->second > 0 &&
          i == cols - it->second) {
        it->second--;
        continue;
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
  int cols = ceil((float)text.size() / rows);
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
      table[i].second[j++] = text[index];
    }
  }
  return table;
}

wstring decrypt_text(wstring text, const wstring key_word) {
  remove_characters(text);

  Table table = init_table(text, key_word);
  vector<int> nums = make_alphabet_num(key_word);

  sort_table(table);
  reverse_sort_table(table, text, nums);

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

wstring encrypt_text(wstring text, const wstring key_word) {
  remove_characters(text);

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