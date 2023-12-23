// Copyright (c) 2023 Dudchenko Olesya Victorovna

#include <iostream>
#include <vector>

template <size_t MaxDegree> class PolinomXYZ {
    vector<double> monoms;
public:
    PolinomXYZ() : monoms(pow(MaxDegree, 3)) {}
    PolinomXYZ(vector<double> coef, vector<vector<size_t>> deg) : monoms(pow(MaxDegree, 3)) {
        size_t degree;
        for (size_t i = 0; i < coef.size(); i++) {
            degree = (deg[i][0] * MaxDegree + deg[i][1]) * MaxDegree + deg[i][2];
            monoms[degree] = coef[i];
        }
    }
    PolinomXYZ operator+(const PolinomXYZ& pol) {
        PolinomXYZ res;
        for (size_t i = 0; i < monoms.size(); i++)
            res.monoms[i] = monoms[i] + pol.monoms[i];
        return res;
    }
    double Calculate(vector<double> point) {
        double value = 0.0;
        size_t monom, degree, kx, ky, kz;
        for (size_t i = 0; i < MaxDegree; i++)
            for (size_t j = 0; j < MaxDegree; j++)
                for (size_t k = 0; k < MaxDegree; k++) {
                    degree = (i * MaxDegree + j) * MaxDegree + k;
                    if (monoms[degree] != 0) {
                        size_t deg[3] = { i, j, k };
                        monom = monoms[degree];
                        for (size_t m = 0; m < point.size(); m++)
                            monom *= pow(point[m], deg[m]);
                        value += monom;
                    }
                }
        return value;
    }
    PolinomXYZ Xderivative()
    {
        PolinomXYZ res;
        size_t degDiff = MaxDegree * MaxDegree;
        for (size_t i = degDiff; i < monoms.size(); i++)
            res.monoms[i - degDiff] = monoms[i] * (i / degDiff);
        for (size_t i = monoms.size() - degDiff; i < monoms.size(); i++)
            res.monoms[i] = 0.0;
        return res;
    }
};