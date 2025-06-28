#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <optional>
#include <memory>
#include "hash_table.h" // Assumed to contain DynamicHashMap, DynamicHashSet, etc.

using namespace std;

class DigitalLibrary {
public:
    virtual vector<string> distinct_words(const string &book_title) = 0;
    virtual int count_distinct_words(const string &book_title) = 0;
    virtual vector<string> search_keyword(const string &keyword) = 0;
    virtual void print_books() = 0;
};

class MuskLibrary : public DigitalLibrary {
private:
    vector<pair<string, vector<string>>> books;

    static vector<string> deep_copy(const vector<string> &arr) {
        return vector<string>(arr);
    }

    static void merge(vector<string> &S1, vector<string> &S2, vector<string> &arr) {
        size_t i = 0, j = 0;
        while (i + j < arr.size()) {
            if (j == S2.size() || (i < S1.size() && S1[i] < S2[j])) {
                arr[i + j] = S1[i++];
            } else {
                arr[i + j] = S2[j++];
            }
        }
    }

    static void merge_sort(vector<string> &arr) {
        if (arr.size() < 2) return;
        size_t mid = arr.size() / 2;
        vector<string> S1(arr.begin(), arr.begin() + mid);
        vector<string> S2(arr.begin() + mid, arr.end());
        merge_sort(S1);
        merge_sort(S2);
        merge(S1, S2, arr);
    }

    static vector<string> distinct_keys(const vector<string> &arr) {
        if (arr.empty()) return {};
        vector<string> result = {arr[0]};
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] != arr[i - 1]) {
                result.push_back(arr[i]);
            }
        }
        return result;
    }

public:
    MuskLibrary(const vector<string> &book_titles, const vector<vector<string>> &texts) {
        vector<pair<string, vector<string>>> L;
        for (size_t i = 0; i < book_titles.size(); ++i) {
            vector<string> copy = deep_copy(texts[i]);
            merge_sort(copy);
            L.emplace_back(book_titles[i], distinct_keys(copy));
        }
        sort(L.begin(), L.end());
        books = L;
    }

    vector<string> distinct_words(const string &book_title) override {
        auto it = lower_bound(books.begin(), books.end(), make_pair(book_title, vector<string>()));
        if (it != books.end() && it->first == book_title) return it->second;
        return {};
    }

    int count_distinct_words(const string &book_title) override {
        return distinct_words(book_title).size();
    }

    vector<string> search_keyword(const string &keyword) override {
        vector<string> result;
        for (const auto &[title, words] : books) {
            if (binary_search(words.begin(), words.end(), keyword)) {
                result.push_back(title);
            }
        }
        return result;
    }

    void print_books() override {
        for (const auto &[title, words] : books) {
            cout << title << ": ";
            for (size_t i = 0; i < words.size(); ++i) {
                cout << words[i];
                if (i + 1 < words.size()) cout << " | ";
            }
            cout << endl;
        }
    }
};

class JGBLibrary : public DigitalLibrary {
private:
    string name;
    vector<int> params;
    string collision_type;
    DynamicHashMap books;

public:
    JGBLibrary(const string &name, const vector<int> &params)
        : name(name), params(params), collision_type(name == "Jobs" ? "Chain" : name == "Gates" ? "Linear" : "Double"),
          books(collision_type, params) {}

    void add_book(const string &book_title, const vector<string> &text) {
        DynamicHashSet words(collision_type, params);
        for (const string &word : text) {
            words.insert(word);
        }
        books.insert(book_title, "");
        books.find(book_title); // trigger lazy init
        for (const string &word : text) {
            books.insert(book_title, word);
        }
    }

    vector<string> distinct_words(const string &book_title) override {
        vector<string> result;
        auto text = books.find(book_title);
        if (text.has_value()) {
            result.push_back(book_title); // Placeholder, requires book-specific text storage
        }
        return result;
    }

    int count_distinct_words(const string &book_title) override {
        return distinct_words(book_title).size();
    }

    vector<string> search_keyword(const string &keyword) override {
        vector<string> result;
        for (const auto &slot : books.linear_table) {
            if (slot) {
                string title = slot->first;
                if (books.find(keyword).has_value()) {
                    result.push_back(title);
                }
            }
        }
        return result;
    }

    void print_books() override {
        books.print_table();
    }
};
