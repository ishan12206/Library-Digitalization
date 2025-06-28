#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <optional>
#include "prime_generator.h"

using namespace std;

int get_next_size(); 

class HashTable {
protected:
    string collision_type;
    vector<int> params;
    int size;
    int count;

    vector<optional<vector<pair<string, string>>>> chain_table;
    vector<optional<pair<string, string>>> linear_table;

public:
    HashTable(string collision_type, vector<int> params)
        : collision_type(collision_type), params(params), count(0) {
        size = params.back();
        if (collision_type == "Chain") {
            chain_table.resize(size);
        } else {
            linear_table.resize(size);
        }
    }

    int get_slot(const string &key, int z1) const {
        unsigned long long hash = 0, pow = 1;
        for (char c : key) {
            if (islower(c)) hash += (c - 'a') * pow;
            else hash += (c - 'A' + 26) * pow;
            pow *= z1;
        }
        return hash % size;
    }

    void insert(pair<string, string> x) {
        string key = x.first;
        int slot = get_slot(key, params[0]);

        if (collision_type == "Chain") {
            if (!chain_table[slot]) chain_table[slot] = vector<pair<string, string>>();
            for (auto &[k, v] : *chain_table[slot]) {
                if (k == key) return;
            }
            chain_table[slot]->push_back(x);
            count++;
        }
        else if (collision_type == "Linear") {
            int probe = slot;
            while (linear_table[probe]) {
                if (linear_table[probe]->first == key) return;
                probe = (probe + 1) % size;
                if (probe == slot) return; // full
            }
            linear_table[probe] = x;
            count++;
        }
        else if (collision_type == "Double") {
            int z2 = params[1], c2 = params[2];
            unsigned long long hash = 0, pow = 1;
            for (char c : key) {
                if (islower(c)) hash += (c - 'a') * pow;
                else hash += (c - 'A' + 26) * pow;
                pow *= z2;
            }
            int step = c2 - (hash % c2);
            int probe = slot;
            while (linear_table[probe]) {
                if (linear_table[probe]->first == key) return;
                probe = (probe + step) % size;
                if (probe == slot) return;
            }
            linear_table[probe] = x;
            count++;
        }
    }

    optional<string> find(const string &key) {
        int slot = get_slot(key, params[0]);

        if (collision_type == "Chain") {
            if (chain_table[slot]) {
                for (auto &[k, v] : *chain_table[slot]) {
                    if (k == key) return v;
                }
            }
            return nullopt;
        }
        else if (collision_type == "Linear") {
            int probe = slot;
            while (linear_table[probe]) {
                if (linear_table[probe]->first == key)
                    return linear_table[probe]->second;
                probe = (probe + 1) % size;
                if (probe == slot) break;
            }
            return nullopt;
        }
        else if (collision_type == "Double") {
            int z2 = params[1], c2 = params[2];
            unsigned long long hash = 0, pow = 1;
            for (char c : key) {
                if (islower(c)) hash += (c - 'a') * pow;
                else hash += (c - 'A' + 26) * pow;
                pow *= z2;
            }
            int step = c2 - (hash % c2);
            int probe = slot;
            while (linear_table[probe]) {
                if (linear_table[probe]->first == key)
                    return linear_table[probe]->second;
                probe = (probe + step) % size;
                if (probe == slot) break;
            }
            return nullopt;
        }
        return nullopt;
    }

    double get_load() const {
        return (double)count / size;
    }

    void print_table() const {
        if (collision_type == "Chain") {
            for (auto &bucket : chain_table) {
                if (!bucket) cout << "<EMPTY> | ";
                else {
                    for (auto &[k, v] : *bucket) cout << "(" << k << ":" << v << ") ";
                    cout << "| ";
                }
            }
        } else {
            for (auto &slot : linear_table) {
                if (!slot) cout << "<EMPTY> | ";
                else cout << "(" << slot->first << ":" << slot->second << ") | ";
            }
        }
        cout << endl;
    }

    virtual void rehash() = 0;
};

class DynamicHashMap : public HashTable {
public:
    DynamicHashMap(string collision_type, vector<int> params)
        : HashTable(collision_type, params) {}

    void insert(const string &key, const string &value) {
        HashTable::insert({key, value});
        if (get_load() >= 0.5) {
            rehash();
        }
    }

    void rehash() override {
        int new_size = get_next_size();
        params.back() = new_size;
        size = new_size;
        count = 0;

        vector<optional<vector<pair<string, string>>>> old_chain = chain_table;
        vector<optional<pair<string, string>>> old_linear = linear_table;

        if (collision_type == "Chain") chain_table = vector<optional<vector<pair<string, string>>>>(size);
        else linear_table = vector<optional<pair<string, string>>>(size);

        if (collision_type == "Chain") {
            for (auto &bucket : old_chain) {
                if (bucket) {
                    for (auto &entry : *bucket) {
                        HashTable::insert(entry);
                    }
                }
            }
        } else {
            for (auto &slot : old_linear) {
                if (slot) {
                    HashTable::insert(*slot);
                }
            }
        }
    }
};

class DynamicHashSet : public HashTable {
public:
    DynamicHashSet(string collision_type, vector<int> params)
        : HashTable(collision_type, params) {}

    void insert(const string &key) {
        HashTable::insert({key, ""});
        if (get_load() >= 0.5) {
            rehash();
        }
    }

    void rehash() override {
        int new_size = get_next_size();
        params.back() = new_size;
        size = new_size;
        count = 0;

        vector<optional<vector<pair<string, string>>>> old_chain = chain_table;
        vector<optional<pair<string, string>>> old_linear = linear_table;

        if (collision_type == "Chain") chain_table = vector<optional<vector<pair<string, string>>>>(size);
        else linear_table = vector<optional<pair<string, string>>>(size);

        if (collision_type == "Chain") {
            for (auto &bucket : old_chain) {
                if (bucket) {
                    for (auto &entry : *bucket) {
                        HashTable::insert(entry);
                    }
                }
            }
        } else {
            for (auto &slot : old_linear) {
                if (slot) {
                    HashTable::insert(*slot);
                }
            }
        }
    }

    bool find(const string &key) {
        return HashTable::find(key).has_value();
    }
};
