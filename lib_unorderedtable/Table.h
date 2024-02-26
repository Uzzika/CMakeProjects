// Copyright (c) 2023 Dudchenko Olesya Victorovna
#pragma once

#include <iostream>
#include "../lib_list/list.h"
#include "../lib_vector/TVector.h"

template <class TKey, class TValue>
class TPair {
    TKey _key;
    TValue _val;
public:
    TPair() = default;
    TPair(TKey key, TValue val) : _key(key), _val(val) {}
    TValue& val() {
        return _val;
    }
    TKey key() {
        return _key;
    }
    bool operator==(const TPair& other) const { return _key == other._key; }
    bool operator==(const TKey& k) const { return _key == k; }
    bool operator!=(const TPair& other) const { return !(_key == other._key); }
    bool operator!=(const TKey& k) const { return !(_key == k); }
};

template <class TKey, class TValue>
class ITable {
    virtual ITable() = default;
    virtual ~ITable() = default;
public:
    virtual ITable(const ITable&) = 0;
    virtual ITable& operator=(const ITable&) = 0;

    virtual TValue* find(const TKey& key) = 0;
    virtual void insert(const TKey& key, const TValue& value) = 0;
    virtual void replace(const TKey& key, const TValue& value) = 0;
    virtual void remove(const TKey& key) = 0;
};

template <class TKey, class TValue>
class UnorderedTable : public ITable<TKey, TValue> {
protected:
    TVector <TPair<TKey, TValue>> data;
public:
    UnorderedTable() = default;
    UnorderedTable(const UnorderedTable &table) : data (table data){}
    void remove(TKey K) override { //на массиве
        size_t ind = find(K);
        if (ind != -1) {
            data[ind] = data[count];
            count--;
        }
    }
    TValue* find(const TKey& K) const override {
        for (int i = 0, i < data.size(), i++) {
            if (data[i] == K) return data[i].val();
        }
    }
    void insert(TKey rkey, TValue rval) const override {
        size_t ind = find(rkey);
        if (ind == -1) {
            TPair<TKey, TValue> tmp(rkey, rval);
            data.append(tmp);
        }
    }
    size_t size() {
        return data.size();
    }
};

template<class TKey, class TValue>
class UnorderedTableOnList : public ITable<TKey, TValue> {
    List < TPair < TKey, TValue>> data;
public:
    UnorderedTableOnList() = default;
    void remove(TKey K) {
    TNode<>*
    pos = find(K);
    if (pos != nullptr) { data.erose(pos); }
    }
    TValue& find(const TKey)
};