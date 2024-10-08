#include "../include/tabular.h"

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
  size_t key_size = key_word.size();
  size_t col_size = table[0].second.size();
  for (size_t i = 0; i < key_size; i++) {
    for (size_t j = 0; j < col_size && index < text.size(); j++) {
      table[i].second[j] = text[index++];
    }
  }
  return table;
}

wstring tab_decrypt(wstring text, const wstring key_word) {
  remove_spaces(text);

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

wstring tab_encrypt(wstring text, const wstring key_word) {
  remove_spaces(text);

  Table table = make_table(text, key_word);
  size_t rows = key_word.size();
  size_t cols = table[0].second.size();
  wstring result_string = L"";
  size_t count = 0;

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

void tab_menu() {
  wstring path;
  wstring key;
  wstring text;
  wstring result;

  wcout << L"\033[2J\033[0;0f";

  while (true) {
    try {
      int choice = choose_interaction();

      if (choice == 3) {
        return;
      } else if (choice > 3 || choice < 1) {
        throw runtime_error("There's no option!");
      }

      wcout << L"\033[2J\033[0;0f";
      wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

      if (choose_method(L"Do you want to read data from a file: (y/n) ")) {
        wcout << L"Enter the path to the file: ";
        getline(wcin, path);

        wifstream file(wstring_to_string(path));

        if (!file.is_open()) {
          throw runtime_error(wstring_to_string(L"Incorrect path"));
        }

        getline(file, key);
        getline(file, text);
        file.close();

      } else {
        wcout << L"Enter the key: ";
        getline(wcin, key);
        wcout << L"Enter the text: ";
        getline(wcin, text);
      }

      if (choice == 1) {
        result = tab_encrypt(text, key);
      } else {
        result = tab_decrypt(text, key);
      }

      if (choose_method(L"Do yow want to write the result to a file? (y/n) ")) {
        wcout << L"Enter the path to the file: ";
        getline(wcin, path);

        wofstream file(wstring_to_string(path));

        file << result;
      } else {
        wcout << result << endl;
      }

      return;

    } catch (const runtime_error &e) {
      wcout << L"Runtime error: ";
      print_error(e.what());
    } catch (const exception &e) {
      wcout << typeid(e).name() << endl;
    }
  }
}
