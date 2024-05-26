// Copyright 2024 Dudchenko Olesya
#pragma once

#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <class TKey, class TValue>
class TPair {
    TKey _key;
    TValue _val;
 public:
    TPair() = default;
    TPair(TKey key, TValue val) : _key(key), _val(val) {}
    TValue& val() { return _val; }
    TKey key() { return _key; }
    bool operator==(const TPair& other) const { return _key == other._key; }
    bool operator==(const TKey& k) const { return _key == k; }
    bool operator!=(const TPair& other) const { return !(_key == other._key); }
    bool operator!=(const TKey& k) const { return !(_key == k); }
    TKey key() const { return _key; }
};

template <class TKey, class TValue>
class ITable {
 public:
    virtual ~ITable() = default;
    virtual TValue* find(const TKey& key) = 0;
    virtual void insert(const TKey& key, const TValue& value) = 0;
    virtual void replace(const TKey& key, const TValue& value) = 0;
    virtual void remove(const TKey& key) = 0;
};

// The class of an unordered table on an array
template <class TKey, class TValue>
class UnorderedTable : public ITable<TKey, TValue> {
protected:
    vector<TPair<TKey, TValue>> data;
    size_t count = 0;
public:
    UnorderedTable() = default;
    UnorderedTable(const UnorderedTable& table) : data(table.data), count(table.count) {}

    // Deletes the pair if the key is found
    void remove(const TKey& K) override {
        for (size_t i = 0; i < count; i++) {
            if (data[i] == K) {
                data[i] = data[count - 1];
                count--;
                return;
            }
        }
    }

    // Replaces the value for an existing key
    void replace(const TKey& key, const TValue& value) override {
        TValue* valPtr = find(key);
        if (valPtr) { *valPtr = value; }
    }

    // Returns a pointer to the value if the key is found, otherwise nullptr
    TValue* find(const TKey& K) override {
        for (size_t i = 0; i < count; i++) {
            if (data[i] == K) return &(data[i].val());
        }
        return nullptr;
    }

    // Adds a new key-value pair if the key is not found
    void insert(const TKey& rkey, const TValue& rval) override {
        if (find(rkey) == nullptr) {
            TPair<TKey, TValue> tmp(rkey, rval);
            data.push_back(tmp);
            count++;
        }
    }

    size_t size() { return data.size(); }
};

// The class of the unordered table on the list
template<class TKey, class TValue>
class UnorderedTableOnList : public ITable<TKey, TValue> {
    list<TPair<TKey, TValue>> data;
public:
    UnorderedTableOnList() = default;

    TValue* find(const TKey& K) override {
        for (auto& pair : data) {
            if (pair == K) return &(pair.val());
        }
        return nullptr;
    }

    void insert(const TKey& rkey, const TValue& rval) override {
        if (find(rkey) == nullptr) { data.emplace_back(rkey, rval); }
    }

    void replace(const TKey& key, const TValue& value) override {
        TValue* valPtr = find(key);
        if (valPtr) { *valPtr = value; }
    }

    void remove(const TKey& K) override {
        data.remove_if([&](const TPair<TKey, TValue>& pair) { return pair == K; });
    }

    size_t size() const { return data.size(); }
};

// The class of an ordered table on an array
template <class TKey, class TValue>
class OrderedTable : public ITable<TKey, TValue> {
protected:
    vector<TPair<TKey, TValue>> data;

    size_t binarySearch(const TKey& key, bool& found) const {
        size_t left = 0;
        size_t right = data.size();
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            if (data[mid].key() < key) {
                left = mid + 1;
            } else if (data[mid].key() > key) {
                right = mid;
            } else {
                found = true;
                return mid;
            }
        }
        found = false;
        return left;
    }

 public:
     OrderedTable() = default;
     OrderedTable(const OrderedTable& table) : data(table.data) {}

    // Returns a pointer to the value if the key is found, otherwise nullptr
     TValue* find(const TKey& key) override {
         bool found;
         size_t index = binarySearch(key, found);
         if (found) { return &(data[index].val()); }
         return nullptr;
     }

    // Adds a new key-value pair to an ordered location
     void insert(const TKey& key, const TValue& value) override {
         bool found;
         size_t index = binarySearch(key, found);
         if (!found) {
             data.insert(data.begin() + index,
                TPair<TKey, TValue>(key, value));
         }
     }

    // Replaces the value for an existing key
     void replace(const TKey& key, const TValue& value) override {
         TValue* valPtr = find(key);
         if (valPtr) { *valPtr = value; }
     }

    // Deletes the pair if the key is found
     void remove(const TKey& key) override {
         bool found;
         size_t index = binarySearch(key, found);
         if (found) { data.erase(data.begin() + index); }
     }

     size_t size() const { return data.size(); }
};
