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

// Класс неупорядоченной таблицы на массиве
template <class TKey, class TValue>
class UnorderedTable : public ITable<TKey, TValue> {
protected:
    TVector <TPair<TKey, TValue>> data;
public:
    UnorderedTable() = default;
    UnorderedTable(const UnorderedTable &table) : data (table data){}
    // Метод remove удаляет пару, если ключ найден
    void remove(const TKey& K) override {
        for (size_t i = 0; i < count; i++) {
            if (data[i] == K) {
                data[i] = data[count - 1];
                count--;
                return;
            }
        }
    }

    // Метод replace заменяет значение для существующего ключа
    void replace(const TKey& key, const TValue& value) override {
        TValue* valPtr = find(key);
        if (valPtr) {
            *valPtr = value;
        }
    }

    // Метод find возвращает указатель на значение,
    // если ключ найден, иначе возвращает nullptr
    TValue* find(const TKey& K) override {
        for (size_t i = 0; i < count; i++) {
            if (data[i] == K) return &(data[i].val());
        }
        return nullptr;
    }

    // Метод insert добавляет новую пару ключ-значение, если ключ не найден
    void insert(const TKey& rkey, const TValue& rval) override {
        if (find(rkey) == nullptr) {
            TPair<TKey, TValue> tmp(rkey, rval);
            data.push_back(tmp);
            count++;
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
    UnorderedTableOnList() = default;

    TValue* find(const TKey& K) override {
        auto node = data.begin();
        while (node != data.end()) {
            if (node->data == K) return &(node->data.val());
            node = node->next;
        }
        return nullptr;
    }

    void insert(const TKey& rkey, const TValue& rval) override {
        if (find(rkey) == nullptr) {
            TPair<TKey, TValue> tmp(rkey, rval);
            data.push_back(tmp);
        }
    }

    void replace(const TKey& key, const TValue& value) override {
        TValue* valPtr = find(key);
        if (valPtr) {
            *valPtr = value;
        }
    }

    void remove(const TKey& K) override {
        auto node = data.begin();
        while (node != data.end()) {
            if (node->data == K) {
                data.erase(node);
                return;
            }
            node = node->next;
        }
    }

    size_t size() const {
        return data.size();
    }
};