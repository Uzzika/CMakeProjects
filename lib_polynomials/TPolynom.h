// Copyright 2024 Dudchenko Olesya

#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include "tmonom.h"
#include "../lib_list/list.h"
#include "theadringlist.h"

class TPolynom {
protected:
    std::string name;
    THeadRingList<TMonom> monoms;

    void tokinize_polynom(const std::string& name);
    bool check_each_char_is_correct(const std::string& name);
    void InsertToSort(const TMonom& monom);
public:
    TPolynom() : monoms() {} // Polynomial "0"
    TPolynom(const std::string& name);
    TPolynom(const THeadRingList<TMonom>& l);
    TPolynom(const TPolynom& p);
    ~TPolynom() = default;

    TPolynom operator-() const;
    TPolynom operator+(const TPolynom& p);
    TPolynom operator-(const TPolynom& p);
    TPolynom operator*(const TPolynom& p);
    bool operator==(const TPolynom& p) const;

    std::string TPolynom::ToString() const;

    double operator()(double x, double y, double z) const;
    TPolynom dx() const;
    TPolynom dy() const;
    TPolynom dz() const;

    const TPolynom& operator=(const TPolynom& p);

    friend std::ostream& operator<< (std::ostream& out, TPolynom& pol) {
        if (pol.monoms.IsEmpty()) {
            out << "Empty!" << "\n";
            return out;
        }
        pol.monoms.Reset();
        while (!pol.monoms.IsEnded()) {
            out << pol.monoms.GetCurr()->data;
            pol.monoms.Next();
        }
        return out;
    }
};
